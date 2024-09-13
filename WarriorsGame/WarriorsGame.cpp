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


Warrior* warrior1;
Warrior* warrior2;

int totalClases = 3;

int normalTextColor = 7;
int failedTextColor = 128;
int critTextColor = 71;

void Gameloop();
void PrintBattleText(Warrior* warriorAttacker, Warrior* warriorReceiver, bool attackState);

int main()
{
	srand(time(NULL));
	Gameloop();
}



void Gameloop()
{
	GenerateRandomWarriors();		


	int battleOrder = rand() % 2;

	bool inBattle = true;
	
	bool attackState;

	if (battleOrder == 0)
	{
		std::cout << "Comienza atacando el guerrero 1." << std::endl;

	}
	else if (battleOrder == 1)
	{
		std::cout << "Comienza atacando el guerrero 2." << std::endl;
	}
	
	std::this_thread::sleep_for(std::chrono::seconds(1));

	while (inBattle)
	{
		if (battleOrder == 0)
		{
			attackState = warrior1->Attack(warrior2);
			PrintBattleText(warrior1, warrior2, attackState);

			if (warrior2->GetHealth() > 0)
			{
				attackState = warrior2->Attack(warrior1);
				PrintBattleText(warrior2, warrior1, attackState);
			}		

		}
		else if (battleOrder == 1)
		{
			attackState = warrior2->Attack(warrior1);
			PrintBattleText(warrior2, warrior1, attackState);

			if (warrior1->GetHealth() > 0)
			{
				attackState = warrior1->Attack(warrior2);
				PrintBattleText(warrior1, warrior2, attackState);
			}			
		}

		if (warrior1->GetHealth() <= 0)
		{
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), normalTextColor);

			std::cout << "El " << warrior1->GetWarriorClass() << " " << warrior1->GetName() << " ha muerto." << std::endl;
			std::this_thread::sleep_for(std::chrono::seconds(2));

			std::cout << "El " << warrior2->GetWarriorClass() << " " << warrior2->GetName() << " ha ganado." << std::endl;
			std::this_thread::sleep_for(std::chrono::seconds(2));

			inBattle = false;
		}
		else if (warrior2->GetHealth() <= 0)
		{
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), normalTextColor);

			std::cout << "El " << warrior2->GetWarriorClass() << " " << warrior2->GetName() << " ha muerto." << std::endl;
			std::this_thread::sleep_for(std::chrono::seconds(2));

			std::cout << "El " << warrior1->GetWarriorClass() << " " << warrior1->GetName() << " ha ganado." << std::endl;
			std::this_thread::sleep_for(std::chrono::seconds(2));

			inBattle = false;
		}

	}

	std::cin.get();

	delete warrior1;
	delete warrior2;
	warrior1 = nullptr;
	warrior2 = nullptr;

	system("cls");
	int input = 0;

	std::cout << "Simular nueva batalla ?" << std::endl;
	std::cout << "1. Si." << std::endl;
	std::cout << "2. No." << std::endl;
	std::cin >> input;
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

	if (input == 1)
	{
		Gameloop();
	}
	
}

void PrintBattleText(Warrior* warriorAttacker, Warrior* warriorReceiver, bool attackState)
{
	bool shieldActive;
	
	if (warriorAttacker->GetWarriorClass() == "Tanque" || warriorAttacker->GetWarriorClass() == "Arquero" && attackState ||
		warriorAttacker->GetWarriorClass() == "Hechicero" && !attackState)	//ATAQUE NORMAL
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), normalTextColor);

		std::cout << "El " << warriorAttacker->GetWarriorClass() << " " << warriorAttacker->GetName() << " ataca! Puntos de danio ejercidos: "
			<< warriorAttacker->GetDamage() << "." << std::endl << std::endl;

		std::this_thread::sleep_for(std::chrono::seconds(2));

		std::cout << "Puntos de vida restantes del " << warriorReceiver->GetWarriorClass() << " " << warriorReceiver->GetName() << ": "
			<< warriorReceiver->GetHealth() << "." << std::endl << std::endl;

		std::this_thread::sleep_for(std::chrono::seconds(2));
	}
	else if (warriorAttacker->GetWarriorClass() == "Arquero" && !attackState)	//ATAQUE NO EXITOSO
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), failedTextColor);
		std::cout << "El " << warriorAttacker->GetWarriorClass() << " " << warriorAttacker->GetName() << " ha fallado en su ataque!" << std::endl
			<< std::endl;

		std::this_thread::sleep_for(std::chrono::seconds(2));

	}
	else if (warriorAttacker->GetWarriorClass() == "Hechicero" && attackState)	//ATAQUE CRITICO
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), critTextColor);

		std::cout << "El " << warriorAttacker->GetWarriorClass() << " " << warriorAttacker->GetName() 
			<< " ataca! Daño critico! Puntos de daño ejercidos: " << warriorAttacker->GetDamage() << "." << std::endl << std::endl;

		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), normalTextColor);

		std::this_thread::sleep_for(std::chrono::seconds(2));

		std::cout << "Puntos de vida restantes del " << warriorReceiver->GetWarriorClass() << " " << warriorReceiver->GetName() << ": "
			<< warriorReceiver->GetHealth() << "." << std::endl << std::endl;

		std::this_thread::sleep_for(std::chrono::seconds(2));

	}
}





