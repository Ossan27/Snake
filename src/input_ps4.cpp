#include "ps4_input.h"
#include "PS4Controller.h"
#include <Arduino.h>

// track last direction to only report changes
static Direction lastDir = Direction::RIGHT;
static bool hasNewDir = false;
static bool initialized = false;
static bool lastOptions = false;

void _ps4_connect(){
    Serial.println("PS4: connected");
}
void _ps4_disconnect(){
    Serial.println("PS4: disconnected");
}
void _ps4_event(){
    // called whenever data arrives - compute a direction based on dpad or analog
    Direction newDir = lastDir;
    if(PS4.Up()) newDir = Direction::UP;
    else if(PS4.Down()) newDir = Direction::DOWN;
    else if(PS4.Left()) newDir = Direction::LEFT;
    else if(PS4.Right()) newDir = Direction::RIGHT;
    else {
        // analog stick threshold
        int8_t lx = PS4.LStickX();
        int8_t ly = PS4.LStickY();
        const int8_t thresh = 60; // adjust for sensitivity
        if(abs(lx) > thresh || abs(ly) > thresh){
            if(abs(lx) > abs(ly)){
                newDir = (lx > 0) ? Direction::RIGHT : Direction::LEFT;
            } else {
                newDir = (ly < 0) ? Direction::UP : Direction::DOWN; // note: y-axis inverted
            }
        }
    }

    if(newDir != lastDir){
        lastDir = newDir;
        hasNewDir = true;
        // debug print
        switch(lastDir){
            case Direction::UP: Serial.println("PS4: dir UP"); break;
            case Direction::DOWN: Serial.println("PS4: dir DOWN"); break;
            case Direction::LEFT: Serial.println("PS4: dir LEFT"); break;
            case Direction::RIGHT: Serial.println("PS4: dir RIGHT"); break;
        }
    }
}

void initPS4Input(){
    if(initialized) return;
    initialized = true;
    // Initialize PS4 library
    PS4.begin("84:17:66:ED:73:40");
    PS4.attach(_ps4_event);
    PS4.attachOnConnect(_ps4_connect);
    PS4.attachOnDisconnect(_ps4_disconnect);
    Serial.println("PS4: init done");
}

bool tryReadPS4Direction(Direction &outDir){
    if(!initialized) return false;
    if(!PS4.isConnected()) return false;
    if(hasNewDir){
        outDir = lastDir;
        hasNewDir = false;
        return true;
    }
    return false;
}

void readPS4AndApplyDirection(Game &game){
    // apply direction changes
    Direction newD;
    if(tryReadPS4Direction(newD)){
        game.setDirection(newD);
    }
    // handle reset / options button as a press event
    if(PS4.isConnected()){
        bool options = PS4.Options();
        if(options && !lastOptions){
            game.reset();
        }
        lastOptions = options;
    }
}
