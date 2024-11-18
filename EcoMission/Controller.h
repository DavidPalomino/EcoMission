#pragma once

#include "Action.h"
#include "Bullet.h"
#include <vector>
#include "Enemy.h"
#include "River.h"
#include "ContaminatedZone.h"

using namespace std;
class Controller {
private:
	vector<Bullet*>Bullets;
	vector<Accion*>Acciones;
	vector<ContaminedZone*>ContaminedZones;
	vector<Enemy*>Enemys;
	vector<River*>Rivers;
	int numberOfContaminedZones;
	int numberOfEnemys;
	int numberOfRivers;
public:
	Controller() {
		numberOfEnemys = 5;
		numberOfContaminedZones = 10;
		numberOfRivers = 1;
	}

	~Controller() {}

	void createEnemy(int width, int height) {
		for (int i = 0; i < numberOfEnemys; i++)
		{
			Enemy* e = new Enemy(width, height, 1);
			Enemys.push_back(e);
		}
	}

	void createContaminedZone(int width, int heigth) {
		for (int i = 0; i < numberOfContaminedZones; i++)
		{
			ContaminedZone* Cz = new ContaminedZone(width, heigth);
			ContaminedZones.push_back(Cz);
		}
	}

	void createRiver(int width, int heigth) {
		for (int i = 0; i < numberOfRivers; i++)
		{
			River* r = new River(width, heigth);
			Rivers.push_back(r);
		}
	}

	void addBullet(Bullet* b) {
		Bullets.push_back(b);
	}

	void addAction(Accion* a) {
		Acciones.push_back(a);
	}

	//Recordar Agregar a bullet denuevo en los parametros
	void drawEveryThing(Graphics^ g, Bitmap^ bmpEnemy, Bitmap^ bmpTrash, Bitmap^ bmpBullet, Bitmap^ bmpRiver, Bitmap^ bmpFertil, Bitmap^ bmpSeed, Bitmap^ bmpTree) {


		for (int i = 0; i < ContaminedZones.size(); i++)
		{
			if (ContaminedZones[i]->getClean() == false) {
				ContaminedZones[i]->draw(g, bmpTrash);
			}

			if (ContaminedZones[i]->getfertil() == true) {
				ContaminedZones[i]->drawFertil(g, bmpFertil);
			}

			if (ContaminedZones[i]->getSeed() == true) {
				ContaminedZones[i]->drawSemilla(g, bmpSeed);
			}

			if (ContaminedZones[i]->getTree() == true) {
				ContaminedZones[i]->drawTree(g, bmpTree);
			}
		}

		for (int i = 0; i < Bullets.size(); i++)
		{
			Bullets[i]->draw(g, bmpBullet);
		}

		for (int i = 0; i < Rivers.size(); i++)
		{
			Rivers[i]->draw(g, bmpRiver);
		}

		for (int i = 0; i < Enemys.size(); i++)
		{
			Enemys[i]->draw(g, bmpEnemy);
		}
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

		for (int i = 0; i < Acciones.size(); i++)
		{
			if (Acciones[i]->getX() <= 0 || Acciones[i]->getXWidth() >= g->VisibleClipBounds.Width ||
				Acciones[i]->getY() <= 0 || Acciones[i]->getYHeight() >= g->VisibleClipBounds.Height) {
				Acciones[i]->setVisibility(false);
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

		for (int i = 0; i < ContaminedZones.size(); i++)
		{
			for (int j = 0; j < Acciones.size(); j++)
			{
				if (ContaminedZones[i]->getRectangle().IntersectsWith(Acciones[j]->getRectangle())&& Acciones[j]->getActionMode() == 1 && ContaminedZones[i]->getClean() == false) {
					ContaminedZones[i]->setClean(true);
					ContaminedZones[i]->setfertil(true);
					Acciones[j]->setVisibility(false);
				}

				if (ContaminedZones[i]->getRectangle().IntersectsWith(Acciones[j]->getRectangle()) && Acciones[j]->getActionMode() == 2 && ContaminedZones[i]->getfertil() == true) {
					ContaminedZones[i]->setfertil(false);
					ContaminedZones[i]->setSeed(true);
					Acciones[j]->setVisibility(false);
				}

				if (ContaminedZones[i]->getRectangle().IntersectsWith(Acciones[j]->getRectangle()) && Acciones[j]->getActionMode() == 3 && ContaminedZones[i]->getSeed() == true) {
					ContaminedZones[i]->setSeed(false);
					ContaminedZones[i]->setTree(true);
					Acciones[j]->setVisibility(false);
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
