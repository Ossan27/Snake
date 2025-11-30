#include "display.h"
#include <Wire.h>

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void initDisplay(){
    Wire.begin();
    if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)){
        // If allocation failed, hang
        while(true){ delay(1000); }
    }
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);
    display.display();
}

void clearDisplay(){ display.clearDisplay(); }
void showDisplay(){ display.display(); }

void drawCell(int gridX, int gridY){
    int x = gridX * CELL_SIZE;
    int y = gridY * CELL_SIZE;
    display.fillRect(x, y, CELL_SIZE, CELL_SIZE, SSD1306_WHITE);
}

void clearCell(int gridX, int gridY){
    int x = gridX * CELL_SIZE;
    int y = gridY * CELL_SIZE;
    display.fillRect(x, y, CELL_SIZE, CELL_SIZE, SSD1306_BLACK);
}

void drawFood(int gridX, int gridY){
    // draw a smaller square at cell center for the food
    int x = gridX * CELL_SIZE + 1;
    int y = gridY * CELL_SIZE + 1;
    int s = max(1, CELL_SIZE - 2);
    display.fillRect(x, y, s, s, SSD1306_WHITE);
}

void drawBorder(){
    display.drawRect(0,0,SCREEN_WIDTH,SCREEN_HEIGHT, SSD1306_WHITE);
}
