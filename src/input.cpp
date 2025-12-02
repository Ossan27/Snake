#include "input.h"
#include "ps4_input.h"
#include <Arduino.h>

void initInput(){
    Serial.begin(115200);
    // initialize PS4 controller support (non-blocking)
    initPS4Input();
}

bool tryReadDirection(Direction &outDir){
    if(!Serial.available()) return false;
    int c = Serial.read();
    if(c == 0x1B){
        // possible arrow key sequence ESC [ A/B/C/D
        // try to read '['
        if(Serial.peek() == '['){
            Serial.read(); // consume '['
            while(!Serial.available()) { delay(1); }
            int third = Serial.read();
            if(third == 'A'){ outDir = Direction::UP; return true; }
            if(third == 'B'){ outDir = Direction::DOWN; return true; }
            if(third == 'C'){ outDir = Direction::RIGHT; return true; }
            if(third == 'D'){ outDir = Direction::LEFT; return true; }
            return false;
        }
    }
    // single char keys
    char ch = (char)c;
    if(ch == 'w' || ch == 'W') { outDir = Direction::UP; return true; }
    if(ch == 's' || ch == 'S') { outDir = Direction::DOWN; return true; }
    if(ch == 'a' || ch == 'A') { outDir = Direction::LEFT; return true; }
    if(ch == 'd' || ch == 'D') { outDir = Direction::RIGHT; return true; }
    // allow numeric keypad arrows (if any): 0x1b + 'OA' etc. but handled above

    return false;
}

void readSerialAndApplyDirection(Game &game){
    Direction newD;
    if(tryReadDirection(newD)){
        game.setDirection(newD);
        return;
    }
    if(Serial.available()){
        char c = Serial.read();
        if(c == 'r' || c == 'R'){
            game.reset();
        }
    }
    // Also keep PS4 input in the loop and apply direction and reset if present
    readPS4AndApplyDirection(game);
}
