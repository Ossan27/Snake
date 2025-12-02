#pragma once

#include "game.h"

void initInput();
// Returns true if direction changed
bool tryReadDirection(Direction &outDir);

void readSerialAndApplyDirection(Game &game); // helper to read serial and set game direction
// PS4 input helper
void initPS4Input();
bool tryReadPS4Direction(Direction &outDir);
void readPS4AndApplyDirection(Game &game);
