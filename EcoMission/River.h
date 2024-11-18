#pragma once
#pragma once

#include <iostream>
using namespace System::Drawing;

class River {
private:
    int x, y;
    int width, height;
    bool visibility;
public:
    River(int w, int h) {
        width = w;
        height = h;
        x = 0;
        y = 380;
    }

    ~River() {}

    // Método para dibujar la zona contaminada
    void draw(Graphics^ g, Bitmap^ bmpRiver) {
        g->DrawImage(bmpRiver, x, y, width , height);
    }

    Rectangle getRectangle() {
        return Rectangle(x, y, width, height);
    }

    int getX() { return x; }
    int getXWidth() { return x + width; }
    int getY() { return y; }
    int getYHeight() { return y + height; }
    void setVisibility(bool v) { visibility = v; }
    bool getVisibility() { return visibility; }
};