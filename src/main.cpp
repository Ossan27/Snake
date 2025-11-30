#include <Arduino.h>

#include "display.h"
#include "game.h"
#include "input.h"

Game game;

void setup(){
  initInput();
  initDisplay();
  randomSeed(analogRead(0));

  game.begin();
}

void loop(){
  readSerialAndApplyDirection(game);
  game.update();
  game.draw();
  delay(10);
}

