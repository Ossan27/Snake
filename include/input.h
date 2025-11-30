#pragma once

#include "game.h"

void initInput();
// Returns true if direction changed
bool tryReadDirection(Direction &outDir);

void readSerialAndApplyDirection(Game &game); // helper to read serial and set game direction
