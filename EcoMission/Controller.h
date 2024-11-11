#pragma once

#include "Bullet.h"
#include <vector>
#include "Enemy.h"

using namespace std;
class Controller {
private:
	vector<Bullet*>Bullets;
	vector<Enemy*>Enemys;
	int numberOfEnemys;
public:
	Controller() {
		numberOfEnemys = 5;
	}

	~Controller() {}

	void createEnemy(int width, int height) {
		for (int i = 0; i < numberOfEnemys; i++)
		{
			Enemy* e = new Enemy(width, height, 1);
			Enemys.push_back(e);
		}
	}

	void addBullet(Bullet* b) {
		Bullets.push_back(b);
	}

	//Recordar Agregar a bullet denuevo en los parametros
	void drawEveryThing(Graphics^ g, Bitmap^ bmpEnemy) {

		for (int i = 0; i < Enemys.size(); i++)
		{
			Enemys[i]->draw(g, bmpEnemy);
		}

		//for (int i = 0; i < Bullets.size(); i++)
		//{
		//	Bullets[i]->draw(g, bmpBullet);
		//}
	}

	void moveEveryThing(Graphics^ g) {

		for (int i = 0; i < Enemys.size(); i++)
		{
			Enemys[i]->move(g);
		}

		for (int i = 0; i < Bullets.size(); i++)
		{
			Bullets[i]->move(g);
		}
	}
	void collision(Graphics^ g) {
		//verificar
		for (int i = 0; i < Bullets.size(); i++)
		{
			if (Bullets[i]->getX() <= 0 || Bullets[i]->getXWidth() >= g->VisibleClipBounds.Width ||
				Bullets[i]->getY() <= 0 || Bullets[i]->getYHeight() >= g->VisibleClipBounds.Height) {
				Bullets[i]->setVisibility(false);
			}
		}

		//colision bullet vs Enemy

		for (int i = 0; i < Enemys.size(); i++)
		{
			for (int j = 0; j < Bullets.size(); j++)
			{
				if (Enemys[i]->getRectangle().IntersectsWith(Bullets[j]->getRectangle())) {
					Enemys[i]->setVisibility(false);
					Bullets[j]->setVisibility(false);
				}
			}
		}

		//borrar
		for (int i = 0; i < Bullets.size(); i++)
		{
			if (!Bullets[i]->getVisibility()) { //if(Bullets[i]->getVisibility()==false)
				Bullets.erase(Bullets.begin() + i);
			}
		}

		for (int i = 0; i < Enemys.size(); i++)
		{
			if (!Enemys[i]->getVisibility()) {
				Enemys.erase(Enemys.begin() + i);
			}
		}

	}
};
