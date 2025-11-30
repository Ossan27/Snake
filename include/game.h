#pragma once

#include <vector>
#include <utility>
#include "display.h"

enum class Direction { UP, DOWN, LEFT, RIGHT };

class Game {
public:
    Game();
    void begin();
    void reset();
    void setDirection(Direction d);
    Direction getDirection() const;
    void update();
    void draw();
    bool isGameOver() const;

private:
    std::vector<std::pair<int,int>> snake; // x,y grid coords, head at front
    std::pair<int,int> food;
    Direction direction;
    unsigned long lastUpdate;
    unsigned long updateInterval; // ms
    bool gameOver;

    void placeFood();
    bool collidesWithSnake(int x, int y) const;
};
