#include <Arduino.h>

#include "display.h"
#include "game.h"
#include "input.h"
#include "WiFiOTAHelper.h"


Game game;
WiFiOTAHelper wifiOta("ESP32-Setup", "setup123", "esp32-dev");


void setup(){
  wifiOta.begin();
  initInput();
  initDisplay();
  game.begin();
}

void loop(){
  wifiOta.handle();
  readSerialAndApplyDirection(game);
  game.update();
  game.draw();
  delay(10);
}

