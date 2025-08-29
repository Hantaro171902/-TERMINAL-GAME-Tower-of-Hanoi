#pragma once 
#include <iostream>

void clearScreen();
void clearTerminal(); // Full terminal reset

void moveCursor(int x, int y);
void hideCursor();
void showCursor();
