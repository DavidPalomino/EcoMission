#pragma once

#include <iostream>
using namespace System::Drawing;

class ContaminedZone {
private:
    int x, y;
    int width, height;
    bool visibility;
    bool clean, fertil, isSeed, isTree;
public:
    ContaminedZone(int w, int h) {
        width = w;
        height = h;
        x = rand() % 800;
        y = rand() % 232;
        visibility = true;
        clean = false;
        fertil = false;
        isSeed = false;
    }

    ~ContaminedZone() {}

    // Método para dibujar la zona contaminada
    void draw(Graphics^ g, Bitmap^ bmpTrash) {
        g->DrawImage(bmpTrash, x, y, width * 0.9, height * 0.9);
    }

    void drawFertil(Graphics^ g, Bitmap^ bmpFertil) {
        g->DrawImage(bmpFertil, x, y, width * 0.9, height * 0.9);
    }

    void drawSemilla(Graphics^ g, Bitmap^ bmpSemilla) {
        g->DrawImage(bmpSemilla, x, y, width * 0.9, height * 0.9);
    }

    void drawTree(Graphics^ g, Bitmap^ bmpTree) {
        g->DrawImage(bmpTree, (x-((width/2)-10)), (y-(height/2)) , width * 1.5, height *1.5);
    }


    Rectangle getRectangle() {
        return Rectangle(x, y, width * 0.9, height * 0.9);
    }

    int getX() { return x; }
    int getXWidth() { return x + width; }
    int getY() { return y; }
    int getYHeight() { return y + height; }

    void setClean(bool c) { clean = c; }
    bool getClean() { return clean; }

    void setfertil(bool f) { this->fertil = f; }
    bool getfertil() { return fertil; }
    
    void setSeed(bool s) { this->isSeed = s; }
    bool getSeed() { return isSeed; }

    void setTree(bool t) { isTree = t; }
    bool getTree() { return isTree; }

    void setVisibility(bool v) { visibility = v; }
    bool getVisibility() { return visibility; }
};
