#pragma once

using namespace System::Drawing;
class Player {
private:
	int x, y; // ubicacion
	int dx, dy; // movimiento
	int idX, idY; // index x e y
	int width, height;
	int widthBoat, heightBoat;
	char direction;
	int mode;
	bool isRiver;
public:
	Player(int w, int h, int wB, int hB) {
		width = w;
		height = h;
		widthBoat = wB;
		heightBoat = hB;
		dx = dy = 8;
		x = 20;
		y = 20;
		idX = idY = 0;
		direction = 'S';
		mode = 1;
		isRiver = false;
	}


	void draw(Graphics^ g, Bitmap^ bmp) {
		Rectangle sectionShow = Rectangle(idX * width, idY * height, width, height);
		Rectangle zoom = Rectangle(x, y, width * 1.0, height * 1.0);
		g->DrawImage(bmp, zoom, sectionShow, GraphicsUnit::Pixel);
	}

	void drawBoat(Graphics^ g, Bitmap^ bmpBoat) {
		g->DrawImage(bmpBoat, x, y, widthBoat, heightBoat);
	}

	void move(Graphics^ g, char i) {
		switch (i)
		{
		case 'A':
			if (x > 0) {
				idY = 9;
				x -= dx;
				direction = 'A';
			}
			break;
		case 'D':
			if (x + width < g->VisibleClipBounds.Width) {
				idY = 11;
				x += dx;
				direction = 'D';
			}
			break;
		case 'W':
			if (y > 0) {
				idY = 8;
				y -= dy;
				direction = 'W';
			}
			break;
		case 'S':
			if (y + height < g->VisibleClipBounds.Height) {
				idY = 10;
				y += dy;
				direction = 'S';
			}
			break;
		}
		idX++;
		if (idX >= 9) idX = 0;
	}

	void moveBoat(Graphics^ g, char i) {
		switch (i)
		{
		case 'A':
			if (x > 0) {
				x -= dx;
				direction = 'A';
			}
			break;
		case 'D':
			if (x + width < g->VisibleClipBounds.Width) {
				x += dx;
				direction = 'D';
			}
			break;
		case 'W':
			if (y > 0) {
				y -= dy;
				direction = 'W';
			}
			break;
		case 'S':
			if (y + height < g->VisibleClipBounds.Height) {
				y += dy;
				direction = 'S';
			}
			break;
		}
	}

	Rectangle getRectangle() {
		return Rectangle(x, y, width * 1.0, height * 1);
	}

	char getDirection() { return direction; }
	int getX() { return x; }
	int getY() { return y; }
	int getHeight() { return height; }
	int getMode() { return mode; }
	void swichMode(int mode) { this->mode = mode; }
	bool getIsRiver() { return isRiver; }
	void swichIsRiver(bool r) { this->isRiver = r; }
};

