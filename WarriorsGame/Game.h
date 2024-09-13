#pragma once
#define NOMINMAX

#include <iostream>
#include <thread>
#include <chrono>
#include <Windows.h>
#include "Warrior.h"
#include "Tank.h"
#include "Archer.h"
#include "Wizard.h"
#include "RandomGen.h"

class Game
{
	private:

		Warrior* warriorGroup1 = nullptr;
		Warrior* warriorGroup2 = nullptr;

		Warrior* warriors1[5];
		Warrior* warriors2[5];

		int normalTextColor = 7;
		int failedTextColor = 128;
		int critTextColor = 71;

		void GenerateRandomWarriors();
		void Gameloop();
		void PrintBattleText(Warrior* attackers, Warrior* receivers, bool attackState);

	public:

		Game();
		virtual ~Game() = 0;

		void InitGame(); //aca va el seed
		void Play();



};

