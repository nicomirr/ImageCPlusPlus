#include "Game.h"

Game::Game()
{
	for (int i = 0; i < 5; i++)
	{
		warriors1[i] = nullptr;
	}

	for (int i = 0; i < 5; i++)
	{
		warriors2[i] = nullptr;
	}

	
}
Game::~Game(){}

void Game::InitGame()
{
	srand(time(NULL));
}

void Game::Play()
{
	Gameloop();
}


void Game::GenerateRandomWarriors()
{
	RandomGen* randomGen = new RandomGen();
	int totalClasses = static_cast<int>(WarriorType::End) - 1;
	int rand = -1;

	for (int i = 0; i < 5; i++)
	{
		rand = randomGen->RandomRange(0, totalClasses);
		
		switch (rand)
		{
			case 0:

				warriors1[i] = new Tank(5, 10, 100, 200, 20, 40);
				break;

			case 1:

				warriors1[i] = new Archer(5, 10, 100, 200);
				break;

			case 2:

				warriors1[i] = new Wizard(5, 10, 100, 200);
				break;

			default:

				break;
		}

		rand = randomGen->RandomRange(0, totalClasses);

		switch (rand)
		{
			case 0:

				warriors2[i] = new Tank(5, 10, 100, 200, 20, 40);
				break;

			case 1:

				warriors2[i] = new Archer(5, 10, 100, 200);
				break;

			case 2:

				warriors2[i] = new Wizard(5, 10, 100, 200);
				break;

			default:

				break;
		}
	}	

	delete randomGen;
	randomGen = nullptr;
}

void Game::Gameloop()
{
	GenerateRandomWarriors();

	int battleOrder = rand() % 2;

	bool inBattle = true;

	bool attackState;

	if (battleOrder == 0)
	{
		std::cout << "Comienza atacando el grupo 1." << std::endl;

	}
	else if (battleOrder == 1)
	{
		std::cout << "Comienza atacando el grupo 2." << std::endl;
	}

	int warriorGroup1Health = 0;
	int warriorGroup2Health = 0;


	while (inBattle)
	{
		warriorGroup1Health = 0;
		warriorGroup2Health = 0;

		if (battleOrder == 0)
		{
			for (int i = 0; i < 5; i++)
			{
				if (warriors1[i]->GetHealth() > 0)
				{
					attackState = warriors1[i]->Attack(warriors2[i]);
					warriorGroup2Health += warriors2[i]->GetHealth();
				}
			}
						
			for (int i = 0; i < 5; i++)
			{
				if (warriorGroup2Health <= 0) return;

				if (warriors2[i]->GetHealth() > 0)
				{
					attackState = warriors2[i]->Attack(warriors1[i]);
					warriorGroup1Health += warriors1[i]->GetHealth();
				}
			}

		}
		else if (battleOrder == 1)
		{
			for (int i = 0; i < 5; i++)
			{
				if (warriors2[i]->GetHealth() > 0)
				{
					attackState = warriors2[i]->Attack(warriors1[i]);
				}
			}

			for (int i = 0; i < 5; i++)
			{
				if (warriorGroup1Health <= 0) return;

				if (warriors1[i]->GetHealth() > 0)
				{
					attackState = warriors1[i]->Attack(warriors2[i]);
				}
			}
		}

		if (warriorGroup1->GetHealth() <= 0)
		{
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), normalTextColor);

			//Perdio grupo 1.

			inBattle = false;
		}
		else if (warriorGroup2->GetHealth() <= 0)
		{
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), normalTextColor);

			//Perdio grupo 2.

			inBattle = false;
		}

		std::cin.get();

		//FALTA HACER LOS NULLPTR
		delete warriorGroup1;
		delete warriorGroup2;
		delete warriors1;
		delete warriors2;


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
}

void Game::PrintBattleText(Warrior* warriorAttacker, Warrior* warriorReceiver, bool attackState)
{
	bool shieldActive;

	if (warriorAttacker->GetWarriorType() == WarriorType::Tank || warriorAttacker->GetWarriorType() == WarriorType::Archer && attackState ||
		warriorAttacker->GetWarriorType() == WarriorType::Wizard && !attackState)	//ATAQUE NORMAL
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), normalTextColor);

		std::cout << "El " << warriorAttacker->GetName() << " ataca! Puntos de danio ejercidos: "
			<< warriorAttacker->GetDamage() << "." << std::endl << std::endl;
			
		std::cout << "Puntos de vida restantes del " <<  warriorReceiver->GetName() << ": "
			<< warriorReceiver->GetHealth() << "." << std::endl << std::endl;

		std::this_thread::sleep_for(std::chrono::seconds(2));
	}
	else if (warriorAttacker->GetWarriorType() == WarriorType::Archer && !attackState)	//ATAQUE NO EXITOSO
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), failedTextColor);
		std::cout << "El " << warriorAttacker->GetName() << " ha fallado en su ataque!" << std::endl
			<< std::endl;

		std::this_thread::sleep_for(std::chrono::seconds(2));

	}
	else if (warriorAttacker->GetWarriorType() == WarriorType::Wizard && attackState)	//ATAQUE CRITICO
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), critTextColor);

		std::cout << "El " << warriorAttacker->GetName() << " ataca! Daño critico! Puntos de daño ejercidos: " 
			<< warriorAttacker->GetDamage() << "." << std::endl << std::endl;

		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), normalTextColor);

		std::this_thread::sleep_for(std::chrono::seconds(2));

		std::cout << "Puntos de vida restantes del " << warriorReceiver->GetName() << ": "
			<< warriorReceiver->GetHealth() << "." << std::endl << std::endl;

		std::this_thread::sleep_for(std::chrono::seconds(2));

	}
}


