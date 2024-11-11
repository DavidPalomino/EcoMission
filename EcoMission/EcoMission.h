#pragma once
#include "Player.h"
#include "Enemy.h"
#include "Controller.h"

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

			bmpPlayer = gcnew Bitmap("images/player.png");
			bmpEnemy = gcnew Bitmap("images/enemyTest.png");
			player = new Player(bmpPlayer->Width / 9, bmpPlayer->Height / 4);

			controller = new Controller();
			controller->createEnemy(bmpEnemy->Width / 4, bmpEnemy->Height / 4);
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
			this->gamePanel->Location = System::Drawing::Point(1, 1);
			this->gamePanel->Name = L"gamePanel";
			this->gamePanel->Size = System::Drawing::Size(833, 611);
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
			player->move(buffer->Graphics, 'A'); break;

		case Keys::D:
			player->move(buffer->Graphics, 'D'); break;

		case Keys::S:
			player->move(buffer->Graphics, 'S'); break;

		case Keys::W:
			player->move(buffer->Graphics, 'W'); break;
		}
	}
	private: System::Void timer1_Tick(System::Object^ sender, System::EventArgs^ e) {
		buffer->Graphics->Clear(Color::WhiteSmoke);

		controller->moveEveryThing(buffer->Graphics);

		player->draw(buffer->Graphics, bmpPlayer);

		controller->drawEveryThing(buffer->Graphics, bmpEnemy);
		buffer->Render(g);
	}
	};
}
