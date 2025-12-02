// PS4 input handling wrapper for Snake game
#pragma once

#include "game.h"

void initPS4Input();
// Returns true if direction changed
bool tryReadPS4Direction(Direction &outDir);
// Helper to read PS4 input and apply to game (direction, reset)
void readPS4AndApplyDirection(Game &game);
