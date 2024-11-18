#pragma once

#include <iostream>
using namespace System::Drawing;

class Bullet {
private:
	int x, y;
	int dx, dy;
	int idX, idY;
	int width, height;
	int direction;
	bool visibility;

public:
	Bullet(int x, int y, int w, int h, char d) {
		width = w;
		height = h;
		direction = d;
		dx = dy = 30;
		idX = idY = 0;
		this->x = x;
		this->y = y;
		visibility = true;
	}
	~Bullet() {}
	void draw(Graphics^ g, Bitmap^ bmp) {
		Rectangle sectionShow = Rectangle(idX * width, idY * height, width, height);
		Rectangle zoom = Rectangle(x, y, width * 0.2, height * 0.2);
		g->DrawImage(bmp, zoom, sectionShow, GraphicsUnit::Pixel);
	}

	void move(Graphics^ g)
	{
		if (direction == 'S' && y + height * 0.2 <= g->VisibleClipBounds.Height) {
			idY = 3;
			y += dy;
			idX++;
			
		}
		if (direction == 'W' && y >= 0) {
			idY = 1;
			y -= dy;
			idX++;
		}
		if (direction == 'A' && x >= 0) {
			idY = 2;
			x -= dx;
			idX++;
		}
		if (direction == 'D' && x + width * 0.2 <= g->VisibleClipBounds.Width) {
			idY = 0;
			x += dx;
			idX++;
		}
		if (idX > 5)
			idX = 0;
	}

	Rectangle getRectangle() {
		return Rectangle(x, y, width *0.02, height * 0.03);
	}
	int getX() { return x; }
	int getXWidth() { return x + width * 0.2; }
	int getY() { return y; }
	int getYHeight() { return y + height * 0.2; }

	void setVisibility(bool v) { visibility = v; }
	bool getVisibility() { return visibility; }

};

