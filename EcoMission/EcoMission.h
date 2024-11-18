#pragma once
#include "Player.h"
#include "Enemy.h"
#include "Controller.h"
#include "Bullet.h"
#include "Action.h"

namespace EcoMission {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for EcoMission
	/// </summary>
	public ref class EcoMission : public System::Windows::Forms::Form
	{
	public:
		EcoMission(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
			g = gamePanel->CreateGraphics();
			space = BufferedGraphicsManager::Current;
			buffer = space->Allocate(g, gamePanel->ClientRectangle);

			bmpPlayer = gcnew Bitmap("Images/ShovelPJ.png");
			bmpEnemy = gcnew Bitmap("Images/enemyTest.png");
			bmpTrash = gcnew Bitmap("Images/trash.png");
			bmpBullet = gcnew Bitmap("Images/bullet.png");
			bmpMap = gcnew Bitmap("Images/Background.png");
			bmpRiver = gcnew Bitmap("Images/Water.png");
			bmpBoat = gcnew Bitmap("Images/BoatTest.png");
			bmpFertil = gcnew Bitmap("Images/fertil.png");
			bmpSeed = gcnew Bitmap("Images/Seed.png");
			bmpTree = gcnew Bitmap("Images/Tree.png");
			player = new Player(bmpPlayer->Width / 13, bmpPlayer->Height / 46, bmpBoat->Width, bmpBoat->Height);

			controller = new Controller();
			controller->createEnemy(bmpEnemy->Width / 4, bmpEnemy->Height / 4);
			controller->createContaminedZone(bmpTrash->Width, bmpTrash->Height);
			controller->createRiver(bmpRiver->Width * 1.5, bmpRiver->Height * 1.5);
			
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~EcoMission()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Panel^ gamePanel;
	protected:

	private: System::ComponentModel::IContainer^ components;


	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		Graphics^ g;
		BufferedGraphicsContext^ space;
		BufferedGraphics^ buffer;
		Bitmap^ bmpPlayer;
		Bitmap^ bmpEnemy;
		Bitmap^ bmpTrash;
		Bitmap^ bmpBullet;
		Bitmap^ bmpMap;
		Bitmap^ bmpRiver;
		Bitmap^ bmpBoat;
		Bitmap^ bmpFertil;
		Bitmap^ bmpSeed;
		Bitmap^ bmpTree;
		Player* player;
	private: System::Windows::Forms::Timer^ timer1;
		   Controller* controller;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			this->gamePanel = (gcnew System::Windows::Forms::Panel());
			this->timer1 = (gcnew System::Windows::Forms::Timer(this->components));
			this->SuspendLayout();
			// 
			// gamePanel
			// 
			this->gamePanel->Location = System::Drawing::Point(0, 0);
			this->gamePanel->Name = L"gamePanel";
			this->gamePanel->Size = System::Drawing::Size(831, 612);
			this->gamePanel->TabIndex = 0;
			this->gamePanel->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &EcoMission::panel1_Paint);
			// 
			// timer1
			// 
			this->timer1->Enabled = true;
			this->timer1->Tick += gcnew System::EventHandler(this, &EcoMission::timer1_Tick);
			// 
			// EcoMission
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(831, 612);
			this->Controls->Add(this->gamePanel);
			this->Name = L"EcoMission";
			this->Text = L"EcoMission";
			this->Load += gcnew System::EventHandler(this, &EcoMission::EcoMission_Load);
			this->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &EcoMission::EcoMission_KeyDown);
			this->ResumeLayout(false);

		}
#pragma endregion
	private: System::Void EcoMission_Load(System::Object^ sender, System::EventArgs^ e) {
	}

	private: System::Void panel1_Paint(System::Object^ sender, System::Windows::Forms::PaintEventArgs^ e) {
	}
	private: System::Void EcoMission_KeyDown(System::Object^ sender, System::Windows::Forms::KeyEventArgs^ e) {
		switch (e->KeyCode)
		{
		case Keys::A:
			if (player->getIsRiver() == false) {
				player->move(buffer->Graphics, 'A');
			}
			else
			{
				player->moveBoat(buffer->Graphics, 'A');
			} break;

		case Keys::D:
			if (player->getIsRiver() == false) {
				player->move(buffer->Graphics, 'D');
			}
			else
			{
				player->moveBoat(buffer->Graphics, 'D');
			} break;

		case Keys::S:
			playerRiver();
			if (player->getIsRiver() == false) {
				player->move(buffer->Graphics, 'S');
			}
			else
			{
				player->moveBoat(buffer->Graphics, 'S');
			}; break;

		case Keys::W:
			playerRiver();
			if (player->getIsRiver() == false) {
				player->move(buffer->Graphics, 'W');
			}
			else
			{
				player->moveBoat(buffer->Graphics, 'W');
			}; break;

		case Keys::D1:
			player->swichMode(1); changePlayerSprite(1); break;

		case Keys::D2:
			player->swichMode(2); changePlayerSprite(2); break;

		case Keys::D3:
			player->swichMode(3); changePlayerSprite(3); break;

		case Keys::D4:
			player->swichMode(4); changePlayerSprite(4); break;
			// Funciona el disparo , lee el posit
		case Keys::Space:
			cleanTrash(player->getMode());
			plantSeed(player->getMode());
			wateringTree(player->getMode());
			shot(player->getMode());
			break;
		}
	}

	void changePlayerSprite(int mode) {
		switch (mode)
		{
		case 1:
			bmpPlayer = gcnew Bitmap("Images/ShovelPJ.png");
			break;
		case 2:
			bmpPlayer = gcnew Bitmap("Images/Player.png");
			break;
		case 3:
			bmpPlayer = gcnew Bitmap("Images/WateringPJ.png");
			break;
		case 4:
			bmpPlayer = gcnew Bitmap("Images/playerWand.png");
			break;
		default:
			break;
		}
	}
	//Boat Things
	int getExactY() {
		int y = (player->getY() + player->getHeight());
		return y;
	}

	void playerRiver() {
		if (getExactY() >= 390) {
			player->swichIsRiver(true);
		}
		else
		{
			player->swichIsRiver(false);
		}
	}

	//Player Action
	//Clean Trash
	void cleanTrash(int m) {
		if (m==1){
			Accion* a = new Accion(player->getX() + 10, player->getY() + 25, bmpBullet->Width / 6, bmpBullet->Height / 4, player->getDirection(), player->getMode());
			controller->addAction(a);
		}
	}

	void plantSeed(int m) {
		if (m == 2) {
			Accion* a = new Accion(player->getX() + 10, player->getY() + 25, bmpBullet->Width / 6, bmpBullet->Height / 4, player->getDirection(), player->getMode());
			controller->addAction(a);
		}
	}

	void wateringTree(int m) {
		if (m == 3) {
			Accion* a = new Accion(player->getX() + 10, player->getY() + 25, bmpBullet->Width / 6, bmpBullet->Height / 4, player->getDirection(), player->getMode());
			controller->addAction(a);
		}
	}

	//Action Shot
	void shot(int m) {
		if(m == 4){
		Bullet* b = new Bullet(player->getX() + 10, player->getY() + 25, bmpBullet->Width / 6, bmpBullet->Height / 4, player->getDirection());
		controller->addBullet(b);
		}
	}

	private: System::Void timer1_Tick(System::Object^ sender, System::EventArgs^ e) {
		buffer->Graphics->Clear(Color::WhiteSmoke);

		controller->collision(g);
		controller->moveEveryThing(buffer->Graphics); 

		buffer->Graphics->DrawImage(bmpMap, 0, 0, bmpMap->Width, bmpMap->Height);
		controller->drawEveryThing(buffer->Graphics, bmpEnemy, bmpTrash, bmpBullet, bmpRiver , bmpFertil, bmpSeed, bmpTree);

		if (player->getIsRiver() == false){
			player->draw(buffer->Graphics, bmpPlayer);
		}
		
		if (player->getIsRiver() == true){
			player->drawBoat(buffer->Graphics, bmpBoat);
		}

		buffer->Render(g);
	}
	};
}
