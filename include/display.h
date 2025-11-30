#pragma once

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// Screen and grid config
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET    -1
#define SCREEN_ADDRESS 0x3C

extern Adafruit_SSD1306 display;

void initDisplay();
void clearDisplay();
void showDisplay();

// drawing helpers working in GRID coordinates
const int CELL_SIZE = 4; // each cell is 4x4 pixels
inline int GRID_WIDTH() { return SCREEN_WIDTH / CELL_SIZE; }
inline int GRID_HEIGHT() { return SCREEN_HEIGHT / CELL_SIZE; }

void drawCell(int gridX, int gridY);
void clearCell(int gridX, int gridY);
void drawFood(int gridX, int gridY);
void drawBorder();
