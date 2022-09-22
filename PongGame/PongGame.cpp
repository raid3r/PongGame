#include <iostream>
#include "console.h"

using namespace std;
const int FIELD_WIDTH = 30;
const int FIELD_HEIGHT = 20;
const int PLATFORM_HEIGHT = 4;

struct Ball {
	float X;
	float Y;
	float shiftX;
	float shiftY;
};



void drawFrame(int height, int width) {
	for (size_t y = 0; y < height; y++)
	{
		for (size_t x = 0; x < width; x++)
		{
			if (x == 0 || y == 0 || x == width - 1 || y == height - 1) {
				SetCursorPosition(x, y);
				SetColor(WHITE, WHITE);
				cout << " ";
			}
		}

	}
	SetColor(WHITE, BLACK);
}
void clearPlatform(COORD& coord) {
	for (size_t y = 0; y < PLATFORM_HEIGHT; y++)
	{
		SetCursorPosition(3, coord.Y + y);
		SetColor(WHITE, BLACK);

		cout << " ";
	}
	SetColor(WHITE, BLACK);
}
void drawPlatform(COORD& coord) {
	for (size_t y = 0; y < PLATFORM_HEIGHT; y++)
	{
		SetCursorPosition(3, coord.Y + y);
		SetColor(WHITE, WHITE);

		cout << " ";
	}
	SetColor(WHITE, BLACK);
}

COORD getBallCoord(const Ball& ball) {
	return { (short)ball.X, (short)ball.Y };
}

void drawBall(Ball& ball) {
	SetCursorPosition(getBallCoord(ball));
	SetColor(WHITE, BLACK);
	cout << "o";
}
void clearBall(Ball& ball) {
	SetCursorPosition(getBallCoord(ball));
	SetColor(WHITE, BLACK);
	cout << " ";
}

float getRandomFloat(float from, int deltaPercent) {
	return from + (rand() % deltaPercent) / 100;
}

void moveBall(Ball& ball, const COORD &platform) {

	Ball newBall = ball;

	newBall.X += ball.shiftX;
	newBall.Y += ball.shiftY;

	if ((short)newBall.X > (float)FIELD_WIDTH - 2) {
		newBall.X = ball.X;
		//newBall.shiftX = 0.7 + (rand() % 50) / 10;
		newBall.shiftX *= -1;
	}

	if ((short)newBall.X < 1.0) {
		newBall.X = ball.X;
		newBall.shiftX *= -1;
		//newBall.shiftX = 0.7 + (rand() % 50) / 10;
	}

	if ((short)newBall.Y > (float)FIELD_HEIGHT - 2) {
		newBall.Y = ball.Y;
		//newBall.shiftY = 0.7 + (rand() % 50) / 10;
		newBall.shiftY *= -1;
	}

	if ((short)newBall.Y < 1.0) {
		newBall.Y = ball.Y;
		newBall.shiftY *= -1;
		//newBall.shiftY = 0.7 + (rand() % 50) / 10;
	}

	/*
	Зареєструвати акаунт на GitHub
	*/

	if ((short)newBall.X == platform.X) {
		if ((short)newBall.Y >= platform.Y && (short)newBall.Y <= platform.Y + PLATFORM_HEIGHT) {
			newBall.X = ball.X; 
			newBall.Y = ball.Y;
			newBall.shiftX *= -1;
			newBall.shiftY *= -1;

			newBall.shiftX += getRandomFloat(-1.2, 120);
			newBall.shiftY += getRandomFloat(-1.2, 120);
			if (newBall.shiftX > 0 && newBall.shiftX < 0.4) {
				newBall.shiftX += getRandomFloat(0.8, 30);
			}

			if (newBall.shiftY > 0 && newBall.shiftY < 0.4) {
				newBall.shiftY += getRandomFloat(0.8, 30);
			}
		
		}
	}

	//Fix 2X speed
	while (newBall.shiftX > 1)
	{
		newBall.shiftX -= 0.05;
	}
	while (newBall.shiftX < -1)
	{
		newBall.shiftX += 0.06;
	}
	while (newBall.shiftY > 1)
	{
		newBall.shiftY -= 0.05;
	}
	while (newBall.shiftY < -1)
	{
		newBall.shiftY += 0.05;
	}

	clearBall(ball);
	ball = newBall;
	drawBall(ball);
}


void setMenuRowColor(const bool isActive) {
	if (isActive) {
		SetColor(BLACK, YELLOW);
	}
	else {
		SetColor(WHITE, BLACK);
	}
}

void drawMenu(const int& activeOption) {
	int x = 3;
	int y = 2;
	SetCursorPosition(x, y++);
	setMenuRowColor(activeOption == 0);
	cout << "Start game";

	SetCursorPosition(x, y++);
	setMenuRowColor(activeOption == 1);
	cout << "Options";

	SetCursorPosition(x, y++);
	setMenuRowColor(activeOption == 2);
	cout << "Exit";

	SetColor(WHITE, BLACK);
}

int startMenu() {
	system("cls");
	int key;
	int activeOption = 0;
	drawFrame(7, 20);
	drawMenu(activeOption);
	while (true)
	{
		key = getKey();

		if (key != -1) {
			switch (key) {
			case UP_ARROW:

				if (activeOption > 0) {
					activeOption--;
				}
				drawMenu(activeOption);

				break;
			case DOWN_ARROW:
				if (activeOption < 2) {
					activeOption++;
				}
				drawMenu(activeOption);
				break;

			case ENTER:
				system("cls");
				return activeOption;

			default:
				break;

			}

		}
		Sleep(50);
	}
}

int main()
{
	ShowConsoleCursor(false);

	int menuOption = startMenu();
	if (menuOption == 2) {
		return 0;
	}

	drawFrame(FIELD_HEIGHT, FIELD_WIDTH);
	int key;
	const int TIME_SHIFT = 10;

	int ballMoveTime = 50;
	int currentTime = 0;

	COORD platform{ 3, 5 };
	Ball ball{ 5.0, 5.0, 1.3, 0.7 };
	drawPlatform(platform);
	drawBall(ball);

	while (true)
	{
		key = getKey();

		SetCursorPosition(50, 3);
		cout << "X  = " << ball.X;
		SetCursorPosition(50, 4);
		cout << "Y  = " << ball.X;
		SetCursorPosition(50, 5);
		cout << "dX = " << ball.shiftX;
		SetCursorPosition(50, 6);
		cout << "dY = " << ball.shiftY;

		if (key != -1) {
			switch (key) {
			case UP_ARROW:

				if (platform.Y > 1) {
					clearPlatform(platform);
					platform.Y--;
					drawPlatform(platform);
				}

				break;
			case DOWN_ARROW:

				if (platform.Y < (FIELD_HEIGHT - 1 - PLATFORM_HEIGHT)) {
					clearPlatform(platform);
					platform.Y++;
					drawPlatform(platform);
				}

				break;
			default:
				break;

			}

		}
		Sleep(TIME_SHIFT);
		currentTime += TIME_SHIFT;

		if (currentTime > ballMoveTime) {
			currentTime = 0;
			moveBall(ball, platform);
		}
	}

}
