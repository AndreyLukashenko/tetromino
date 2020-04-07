// Copyright 2009-2014 Blam Games, Inc. All Rights Reserved.

#pragma once

#include "BaseApp.h";
#include "Tetromino.h";

const int FieldWidth = 25;
const int FieldHeight = 25;
const int PlayFieldWidth = 15;
const int PlayFieldHeight = 20;
const float speedInitial = 0.4f;
const float speedFast = 0.05f;


class TestApp : public BaseApp
{
	typedef BaseApp Parent;

private:
	int mObj1XOld;
	int mObj1YOld;
	int mObj1X;
	int mObj1Y;

	int mObj2X;
	int mObj2Y;

	bool mDirection;

	Tetromino * tetronimo;
	int nextTetromino;
	int reflection;
	int score;
	float speed;
	float speedDelay;

public:
	TestApp();
	virtual void KeyPressed(int btnCode);
	virtual void UpdateF(float deltaTime);
	void drawField();
	bool createTetronimo();
	Tetromino * makeTetronimo(int selectedTetronimo);
	void drawTetronimo();
	void clearTetronimo();
	void drawNextTetronimo();
	void clearNextTetronimo();
	void fixTetronimo();
	bool isRotate();

	void ShowScore();
	bool CollisionLeft();
	bool CollisionRight();
	bool CollisionBottom();
	void FillStroke();
};
