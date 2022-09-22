#pragma once

#include <windows.h>
#include <conio.h>


// Console colors
enum ConsoleColor {
	// Standard text colors
	GRAY = 8, BLUE, GREEN,
	TEAL, RED, PINK,
	YELLOW, WHITE,
	// Faded text colors
	BLACK = 0, BLUE_FADE, GREEN_FADE,
	TEAL_FADE, RED_FADE, PINK_FADE,
	YELLOW_FADE, WHITE_FADE,
};

void SetColor(ConsoleColor text, ConsoleColor background = BLACK);

void SetColor(short text, short background = BLACK);

void ResetColor();

void SetCursorPosition(const COORD& coord);

void SetCursorPosition(const COORD& coord);

void ShowConsoleCursor(bool showFlag);

void SetCursorPosition(short x, short y);

enum Keys {
	BACKSPACE = 8,
	ESC = 27, ARROW_START = 224, ENTER = 13, SPACE = 32,
	UP_ARROW = 72, DOWN_ARROW = 80, LEFT_ARROW = 75, RIGHT_ARROW = 77
};

int getKey();