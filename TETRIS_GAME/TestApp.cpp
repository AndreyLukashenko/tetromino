// Copyright 2009-2014 Blam Games, Inc. All Rights Reserved.
#include "stdafx.h"
#include <iostream>
#include <conio.h>
#include <ctime>
#include <memory>
#include <cstdlib>
#include "TestApp.h"

TestApp::TestApp() : Parent(FieldWidth, FieldHeight)
{
	mObj2X = 20;
	mObj2Y = 5;
	srand(time(0));
	nextTetromino = rand() % 5;
	reflection = rand() % 1;
	score = 0;
	speed = speedInitial;
	speedDelay = 0;
	createTetronimo();
}

void TestApp::KeyPressed(int btnCode)
{
	if (speed == speedFast)
		return;
	else if (btnCode == 224)
		btnCode = _getch();
	switch (btnCode) {
	case 80:
		mObj1Y++;
		speed = speedFast;
		break;
	case 75:
		if (CollisionLeft())
			--mObj1X;
		break;
	case 77:
		if (CollisionRight())
			++mObj1X;
		break;
	case 32:
		clearTetronimo();
		if (isRotate())
			tetronimo->rotate();
	}
}

void TestApp::UpdateF(float deltaTime)
{
	clearTetronimo();
	drawField();
	FillStroke();
	speedDelay += deltaTime;
	if (speedDelay > speed) {
		speedDelay = 0;
		if (CollisionBottom()) {
			++mObj1Y;
		}
		else {
			fixTetronimo();
			if (!createTetronimo()) {
				exit(0);
			}

		}
	}

	drawTetronimo();
	ShowScore();

	mObj1XOld = mObj1X;
	mObj1YOld = mObj1Y;
}
void TestApp::drawField() {
	// draw border
	for (int i = 0; i <= FieldWidth; ++i) {
		SetChar(i, 0, '#');
		SetChar(i, FieldHeight, '#');
		SetChar(0, i, '#');
		SetChar(FieldWidth, i, '#');
		SetChar(i, PlayFieldHeight + 1, '#');
	}

	// draw play field line 
	for (int y = 1; y <= PlayFieldHeight; ++y) {
		SetChar(PlayFieldWidth + 1, y, '#');
	}

	//draw play border
	for (int x = 1; x <= PlayFieldWidth; ++x) {
		for (int y = 1; y <= PlayFieldHeight; ++y) {
			if (GetChar(x, y) != FIGURE_FILL) {
				SetChar(x, y, '.');
			}
		}
	}
}

bool TestApp::createTetronimo() {
	mObj1XOld = mObj1X = 7;
	mObj1YOld = mObj1Y = 1;
	speed = speedInitial;

	tetronimo = makeTetronimo(nextTetromino);

	for (size_t x = 0; x < tetronimo->getSizeX(); ++x) {
		for (size_t y = 0; y < tetronimo->getSizeY(); ++y) {
			if (tetronimo->figure[x][y] != L' ' &&
				GetChar(mObj1X + y, mObj1Y + x) == FIGURE_FILL)
				return false;
		}
	}

	srand(time(0));
	reflection = static_cast<bool>(rand() % 2);
	nextTetromino = rand() % 5;
	drawNextTetronimo();

	return true;
}

Tetromino * TestApp::makeTetronimo(int selectedTetronimo) {
	switch (selectedTetronimo) {
	case 0:
		return new T(2, 3);
		break;
	case 1:
		return new I(4, 1);
		break;
	case 2:
		return new L(reflection, 3, 2);
		break;
	case 3:
		return new Z(reflection, 2, 3);
		break;
	case 4:
		return new O(2, 2);
		break;
	}
}


void TestApp::drawTetronimo() {
	for (size_t x = 0; x < tetronimo->getSizeX(); ++x) {
		for (size_t y = 0; y < tetronimo->getSizeY(); ++y) {
			if (tetronimo->figure[x][y] != L' ') {
				SetChar(mObj1X + y, mObj1Y + x, tetronimo->figure[x][y]);
			}
		}
	}
}

void TestApp::clearTetronimo() {
	for (size_t x = 0; x < tetronimo->getSizeX(); ++x) {
		for (size_t y = 0; y < tetronimo->getSizeY(); ++y) {
			if (tetronimo->figure[x][y] != L' ') {
				SetChar(mObj1XOld + y, mObj1YOld + x, '.');
			}
		}
	}
}

void TestApp::drawNextTetronimo() {
	clearNextTetronimo();

	Tetromino* next = makeTetronimo(nextTetromino);

	for (size_t x = 0; x < next->getSizeX(); ++x) {
		for (size_t y = 0; y < next->getSizeY(); ++y) {
			if (next->figure[x][y] != L' ') {
				SetChar(mObj2X + y, mObj2Y + x, next->figure[x][y]);
			}
		}
	}

	delete next;
}

void TestApp::clearNextTetronimo() {
	for (size_t x = 0; x < 4; ++x) {
		for (size_t y = 0; y < 3; ++y) {
			SetChar(mObj2X + y, mObj2Y + x, L' ');
		}
	}
}

void TestApp::fixTetronimo() {
	for (size_t x = 0; x < tetronimo->getSizeX(); ++x) {
		for (size_t y = 0; y < tetronimo->getSizeY(); ++y) {
			if (tetronimo->figure[x][y] != L' ') {
				SetChar(mObj1X + y, mObj1Y + x, FIGURE_FILL);
			}
		}
	}

	this->tetronimo->clearFigure();
	this->tetronimo = nullptr;
}


bool TestApp::CollisionLeft() {

	for (size_t x = 0; x < tetronimo->getSizeX(); ++x) {
		for (size_t y = 0; y < tetronimo->getSizeY(); ++y) {
			if (tetronimo->figure[x][y] != L' ') {
				if (GetChar(mObj1X + y - 1, mObj1Y + x) != '.') {
					return false;
				}
				else
					break;
			}
		}
	}
	return true;
}

bool TestApp::CollisionRight() {

	for (size_t x = 0; x < tetronimo->getSizeX(); ++x) {
		for (size_t y = tetronimo->getSizeY(); y >= 0; --y) {
			if (tetronimo->figure[x][y] != L' ') {
				if (GetChar(mObj1X + y, mObj1Y + x) != '.') {
					return false;
				}
				else
					break;
			}
		}
	}
	return true;
}

bool TestApp::CollisionBottom() {
	if (mObj1Y + tetronimo->getSizeX() > PlayFieldHeight) {
		return false;
	}

	for (size_t x = 0; x < tetronimo->getSizeX(); ++x) {
		for (size_t y = 0; y < tetronimo->getSizeY(); ++y) {
			if (tetronimo->figure[x][y] != L' ') {
				if (GetChar(mObj1X + y, mObj1Y + x + 1) == FIGURE_FILL) {
					return false;
				}
			}
		}
	}
	return true;
}

bool TestApp::isRotate() {
	std::unique_ptr<Tetromino> temp = std::make_unique<Tetromino>(*tetronimo);
	temp->rotate();

	for (size_t x = 0; x < temp->getSizeX(); ++x) {
		for (size_t y = 0; y < temp->getSizeY(); ++y) {
			if (temp->figure[x][y] != L' ' &&
				GetChar(mObj1X + y, mObj1Y + x) != '.') {
				return false;
			}
		}
	}

	return true;
}

void TestApp::FillStroke() {
	bool fill = false;
	for (size_t y = PlayFieldHeight; y > 0; --y) {
		for (size_t x = 1; x <= PlayFieldWidth; ++x) {
			if (GetChar(x, y) == '.')
				break;
			else
				if (x == PlayFieldWidth) {
					fill = true;
				}
				else
					continue;
		}

		if (fill) {
			for (size_t x = 1; x <= PlayFieldWidth; ++x) {
				SetChar(x, y, '.');
			}

			for (size_t yy = y; yy > 1; --yy) {
				for (size_t x = 1; x <= PlayFieldWidth; ++x) {
					SetChar(x, yy, GetChar(x, yy - 1));
				}
			}

			score += 100;
			return;
		}

	}
}

void TestApp::ShowScore() {

	string score_text = "> Score: ";

	for (int i = 0; i < score_text.length(); ++i) {
		SetChar(3 + i, 23, score_text[i]);
	}

	string result = std::to_string(score);

	for (int i = 0; i < result.length(); ++i) {
		SetChar(3 + score_text.length() + i, 23, result[i]);
	}

}

