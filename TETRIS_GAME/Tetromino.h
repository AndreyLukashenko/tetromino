#pragma once

const wchar_t FIGURE_FILL = L'$';

class Tetromino
{
public:
	Tetromino();
	Tetromino(int size_x, int size_y);
	Tetromino(const Tetromino &obj);
	virtual ~Tetromino();

	wchar_t** figure;

	int getSizeX() const;
	int getSizeY() const;
	void figureInit();
	void clearFigure();
	virtual void reflection();
	virtual void rotate();
private:
	int size_x;
	int size_y;
};


class T : public Tetromino {
public:
	T(int size_x = 2, int size_y = 3);
	void rotate() override;
};

class I : public Tetromino {
public:
	I(int size_x = 4, int size_y = 1);
	void rotate() override;
};

class L : public Tetromino {
public:
	L(bool reflection, int size_x = 3, int size_y = 2);
	void reflection() override;
	void rotate() override;
};

class Z : public Tetromino {
public:
	Z(bool reflection, int size_x = 2, int size_y = 3);
	void reflection() override;
	void rotate() override;
};

class O : public Tetromino {
public:
	O(int size_x = 2, int size_y = 2);
	void rotate() override;
};

