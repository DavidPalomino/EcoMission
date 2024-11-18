#pragma once
#include <iostream>
using namespace System::Drawing;

class Accion {
private:
	int x, y;
	int lx, ly;
	int dx, dy;
	int idX, idY;
	int width, height;
	int direction;
	bool visibility;
	int mode;
public:
	Accion(int x, int y, int w, int h, char d, int m) {
		width = w;
		height = h;
		direction = d;
		dx = dy = 30;
		idX = idY = 0;
		this->x = x;
		this->y = y;
		this->lx = x;
		this->ly = y;
		this->mode = m;
		visibility = true;
	}
	~Accion() {}
	void draw(Graphics^ g, Bitmap^ bmp) {
		Rectangle sectionShow = Rectangle(idX * width, idY * height, width, height);
		Rectangle zoom = Rectangle(x, y, width * 0.2, height * 0.2);
		g->DrawImage(bmp, zoom, sectionShow, GraphicsUnit::Pixel);
	}

	void move(Graphics^ g)
	{
		if (direction == 'S' && y <= ly + 20) {
			idY = 1;
			y += dy;
			idX++;

		}
		if (direction == 'W' && y >= ly - 20) {
			idY = 1;
			y -= dy;
			idX++;
		}
		if (direction == 'A' && x >= lx - 20) {
			idY = 1;
			x -= dx;
			idX++;
		}
		if (direction == 'D' && x <= lx + 20) {
			idY = 1;
			x += dx;
			idX++;
		}
		if (idX > 5)
			idX = 0;
	}

	Rectangle getRectangle() {
		return Rectangle(x, y, width * 0.15, height * 0.05);
	}
	int getX() { return x; }
	int getXWidth() { return x + width * 0.2; }
	int getY() { return y; }
	int getYHeight() { return y + height * 0.2; }

	void setActionMode(int m) { mode = m; }
	int getActionMode() { return mode; }

	void setVisibility(bool v) { visibility = v; }
	bool getVisibility() { return visibility; }

};

