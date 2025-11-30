#include "game.h"
#include <Arduino.h>
#include <stdlib.h>

Game::Game()
: direction(Direction::RIGHT), lastUpdate(0), updateInterval(250), gameOver(false)
{
}

void Game::begin(){
    reset();
}

void Game::reset(){
    snake.clear();
    // starting snake length 3 centered horizontally
    int startX = GRID_WIDTH() / 2;
    int startY = GRID_HEIGHT() / 2;

    snake.push_back({startX, startY});
    snake.push_back({startX - 1, startY});
    snake.push_back({startX - 2, startY});

    direction = Direction::RIGHT;
    updateInterval = 250; // ms per step, can be lowered as it grows or as level
    lastUpdate = millis();
    gameOver = false;
    placeFood();
}

void Game::setDirection(Direction d){
    // prevent reversing
    if((direction == Direction::UP && d == Direction::DOWN) ||
       (direction == Direction::DOWN && d == Direction::UP) ||
       (direction == Direction::LEFT && d == Direction::RIGHT) ||
       (direction == Direction::RIGHT && d == Direction::LEFT)){
        return; // ignore reverse
    }
    direction = d;
}

Direction Game::getDirection() const { return direction; }

bool Game::isGameOver() const { return gameOver; }

void Game::placeFood(){
    int fx, fy;
    do {
        fx = random(0, GRID_WIDTH());
        fy = random(0, GRID_HEIGHT());
    } while(collidesWithSnake(fx, fy));
    food = {fx, fy};
}

bool Game::collidesWithSnake(int x, int y) const {
    for(auto &p : snake){
        if(p.first == x && p.second == y) return true;
    }
    return false;
}

void Game::update(){
    if(gameOver) return;
    unsigned long now = millis();
    if(now - lastUpdate < updateInterval) return;
    lastUpdate = now;

    // move
    auto head = snake.front();
    int nx = head.first;
    int ny = head.second;
    switch(direction){
        case Direction::UP: ny -= 1; break;
        case Direction::DOWN: ny += 1; break;
        case Direction::LEFT: nx -= 1; break;
        case Direction::RIGHT: nx += 1; break;
    }

    // wrap-around
    if(nx < 0) nx = GRID_WIDTH() - 1;
    if(nx >= GRID_WIDTH()) nx = 0;
    if(ny < 0) ny = GRID_HEIGHT() - 1;
    if(ny >= GRID_HEIGHT()) ny = 0;

    if(collidesWithSnake(nx, ny)){
        // if collides with tail except maybe last segment (since it's moving forward)
        gameOver = true;
        return;
    }

    // add new head
    snake.insert(snake.begin(), {nx, ny});

    if(nx == food.first && ny == food.second){
        // eat - place new food, and maybe speed up
        placeFood();
        if(updateInterval > 80) updateInterval -= 10; // speed up a bit
    } else {
        // remove tail
        snake.pop_back();
    }
}

void Game::draw(){
    clearDisplay();
    drawBorder();

    // draw food
    drawFood(food.first, food.second);
    // draw snake
    bool headDrawn = false;
    for(size_t i=0;i<snake.size();i++){
        int x = snake[i].first;
        int y = snake[i].second;
        drawCell(x, y);
    }

    // show score as text
    display.setCursor(2, 0);
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);
    display.print("Len:"); display.print((int)snake.size());

    if(gameOver){
        display.setCursor(40, 12);
        display.setTextSize(1);
        display.println("GAME OVER");
    }

    showDisplay();
}
