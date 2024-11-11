#pragma once

#include <iostream>
using namespace System::Drawing;

class Enemy {
private:
	int x, y;
	int dx, dy;
	int idX, idY;
	int width, height;
	int direccion;
	bool visibility;

public:
	Enemy(int w, int h, int d) {
		width = w;
		height = h;
		direccion = d;
		dx = dy = 20;
		x = rand() % 900;
		y = rand() % 200;
		idX = idY = 0;
		visibility = true;
	}
	~Enemy() {}

	void draw(Graphics^ g, Bitmap^ bmp) {
		Rectangle sectionShow = Rectangle(idX * width, idY * height, width, height);
		Rectangle zoom = Rectangle(x, y, width, height);
		g->DrawImage(bmp, zoom, sectionShow, GraphicsUnit::Pixel);
	}

	void move(Graphics^ g) {
		if (direccion == 1) { // los enemigos se mueven de izquierda a derecha
			if (x + width * 1.0 > g->VisibleClipBounds.Width || x < 0) dx *= -1;
			if (dx > 0) { //dx=20
				idY = 2;
			}
			else // dx=-20
				idY = 1;
			x += dx;
		}
		else {
			if (y + height * 1.0 > g->VisibleClipBounds.Height || y < 0) dy *= -1;

			if (dy > 0) {
				idY = 0;
			}
			else
				idY = 3;
			y += dy;

		}
		idX++;
		if (idX > 3)
			idX = 0;
	}
	Rectangle getRectangle() {
		return Rectangle(x, y, width * 1.0, height * 1.0);
	}

	void setVisibility(bool v) { visibility = v; }
	bool getVisibility() { return visibility; }

};

