#include "stdafx.h"
#include "Tetromino.h"
#include <utility>
#include <memory>

Tetromino::Tetromino() {

}

Tetromino::Tetromino(int size_x, int size_y)
{
	this->size_x = size_x;
	this->size_y = size_y;
	figureInit();
}

Tetromino::Tetromino(const Tetromino &obj) {
	this->size_x = obj.size_x;
	this->size_y = obj.size_y;
	figureInit();

	for (size_t x = 0; x < size_x; ++x) {
		for (size_t y = 0; y < size_y; ++y) {
			this->figure[x][y] = obj.figure[x][y];
		}
	}
}


int Tetromino::getSizeX() const {
	return size_x;
}

int Tetromino::getSizeY() const {
	return size_y;
}

void Tetromino::figureInit() {
	figure = new wchar_t*[size_x];
	for (size_t i = 0; i < size_x; ++i) {
		figure[i] = new wchar_t[size_y];
	}

	for (size_t x = 0; x < size_x; ++x) {
		for (size_t y = 0; y < size_y; ++y) {
			figure[x][y] = L' ';
		}
	}
}

void Tetromino::clearFigure() {
	for (size_t i = 0; i < size_x; ++i) {
		delete[] figure[i];
	}

	delete[] figure;
}

void Tetromino::reflection() {}

void Tetromino::rotate() {

	std::unique_ptr<Tetromino> tempObj = std::make_unique<Tetromino>(*this);

	clearFigure();
	int temp = size_x;
	size_x = size_y;
	size_y = temp;
	figureInit();

	for (size_t x = 0; x < size_x; ++x) {
		for (size_t y = 0; y < size_y; ++y) {
			figure[x][y] = tempObj->figure[y][size_x - x - 1];
		}
	}
}

Tetromino::~Tetromino()
{
	clearFigure();
}


T::T(int size_x, int size_y) : Tetromino(size_x, size_y) {
	figure[0][1] = FIGURE_FILL;
	figure[1][0] = FIGURE_FILL;
	figure[1][1] = FIGURE_FILL;
	figure[1][2] = FIGURE_FILL;
}

void T::rotate() {
	Tetromino::rotate();
}

I::I(int size_x, int size_y) : Tetromino(size_x, size_y) {
	figure[0][0] = FIGURE_FILL;
	figure[1][0] = FIGURE_FILL;
	figure[2][0] = FIGURE_FILL;
	figure[3][0] = FIGURE_FILL;
}

void I::rotate() {
	Tetromino::rotate();
}

L::L(bool reflection, int size_x, int size_y) : Tetromino(size_x, size_y) {
	figure[0][0] = FIGURE_FILL;
	figure[1][0] = FIGURE_FILL;
	figure[2][0] = FIGURE_FILL;
	figure[2][1] = FIGURE_FILL;
	if (reflection) {
		this->reflection();
	}
}

void L::reflection() {
	for (size_t y = 0; y < getSizeY(); ++y) {
		std::swap(figure[y][0], figure[y][1]);
	}
}

void L::rotate() {
	Tetromino::rotate();
}

Z::Z(bool reflection, int size_x, int size_y) : Tetromino(size_x, size_y) {
	figure[0][0] = FIGURE_FILL;
	figure[0][1] = FIGURE_FILL;
	figure[1][1] = FIGURE_FILL;
	figure[1][2] = FIGURE_FILL;
	if (reflection) {
		this->reflection();
	}
}

void Z::reflection() {
	std::swap(figure[0], figure[1]);
}

void Z::rotate() {
	Tetromino::rotate();
}

O::O(int size_x, int size_y) : Tetromino(size_x, size_y) {
	figure[0][0] = FIGURE_FILL;
	figure[0][1] = FIGURE_FILL;
	figure[1][0] = FIGURE_FILL;
	figure[1][1] = FIGURE_FILL;
}

void O::rotate() {

}





