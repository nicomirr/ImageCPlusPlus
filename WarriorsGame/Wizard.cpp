#include "Wizard.h"


Wizard::Wizard(int minPossibleDamage, int maxPossibleDamage, int minPossibleHealth, int maxPossibleHealth)
{
	RandomGen* randomGen = new RandomGen();

	this->name = "Hechicero";
	this->warriorType = WarriorType::Wizard;
	
	SetDamage(randomGen->RandomRange(minPossibleDamage, maxPossibleDamage));
	SetHealth(randomGen->RandomRange(minPossibleHealth, maxPossibleHealth));
	this->normalDamage = GetDamage();
	this->critChance = 25;
	this->critMultiplier = 2;
	
	std::cout << "Hechicero " << this->name << " creado." << std::endl;;
	ShowStatistics();

	delete randomGen;

}

Wizard::~Wizard()
{
	std::cout << "Hechicero " << this->name << " destruido." << std::endl;;
}

bool Wizard::CheckCritSuccess()
{
	return (rand() % 100) + 1 <= this->critChance ? true : false;
}

void Wizard::DrawWarriorIdle(bool isLeftSide, int yCursorPos)
{
	if (GetHealth() <= 0)
	{
		DrawWarriorDead(isLeftSide, yCursorPos);
		return;
	}

	if (isLeftSide)
	{
		CursorOptions::SetCursorPosition(0, yCursorPos);
		std::cout << "                                      ";
		yCursorPos++;

		CursorOptions::SetCursorPosition(0, yCursorPos);
		std::cout << "                                      ";
		yCursorPos++;

		CursorOptions::SetCursorPosition(0, yCursorPos);
		std::cout << "                              _    _   ";
		yCursorPos++;

		CursorOptions::SetCursorPosition(0, yCursorPos);
		std::cout << "                             |_|  |    ";
		yCursorPos++;

		CursorOptions::SetCursorPosition(0, yCursorPos);
		std::cout << "             HEALTH: " << std::setfill('0') << std::setw(2) << GetHealth() << "     /| |\\ | ";
		yCursorPos++;

		CursorOptions::SetCursorPosition(0, yCursorPos);
		std::cout << "                            ||_| \\|   ";
		yCursorPos++;

		CursorOptions::SetCursorPosition(0, yCursorPos);
		std::cout << "                             | |  |    ";

	}
	else
	{
		CursorOptions::SetCursorPosition(xCursorPosDraw, yCursorPos);
		std::cout << "                    ";
		yCursorPos++;

		CursorOptions::SetCursorPosition(xCursorPosDraw, yCursorPos);
		std::cout << "                    ";
		yCursorPos++;

		CursorOptions::SetCursorPosition(xCursorPosDraw, yCursorPos);
		std::cout << "        _    _      ";
		yCursorPos++;

		CursorOptions::SetCursorPosition(xCursorPosDraw, yCursorPos);
		std::cout << "         |  |_|     ";
		yCursorPos++;

		CursorOptions::SetCursorPosition(xCursorPosDraw, yCursorPos);
		std::cout << "         | /| |\\    " << "HEALTH: " << std::setfill('0') << std::setw(2) << GetHealth();
		yCursorPos++;

		CursorOptions::SetCursorPosition(xCursorPosDraw, yCursorPos);
		std::cout << "         |/ |_||    ";
		yCursorPos++;

		CursorOptions::SetCursorPosition(xCursorPosDraw, yCursorPos);
		std::cout << "         |  | |     ";
	}
}

void Wizard::DrawWarriorAttack(bool isLeftSide, int yCursorPos)
{
	if (isLeftSide)
	{
		CursorOptions::SetCursorPosition(0, yCursorPos);
		std::cout << "                                      ";
		yCursorPos++;

		CursorOptions::SetCursorPosition(0, yCursorPos);
		std::cout << "                                     _      ";
		yCursorPos++;

		CursorOptions::SetCursorPosition(0, yCursorPos);
		std::cout << "                              _     /       ";
		yCursorPos++;

		CursorOptions::SetCursorPosition(0, yCursorPos);
		std::cout << "                             |_|   /    <*) ";
		yCursorPos++;

		CursorOptions::SetCursorPosition(0, yCursorPos);
		std::cout << "             HEALTH: " << std::setfill('0') << std::setw(2) << GetHealth() << "     /| |\\_/ ";
		yCursorPos++;

		CursorOptions::SetCursorPosition(0, yCursorPos);
		std::cout << "                            ||_| /          ";
		yCursorPos++;

		CursorOptions::SetCursorPosition(0, yCursorPos);
		std::cout << "                             | |            ";
	}
	else
	{
		CursorOptions::SetCursorPosition(xCursorPosDraw, yCursorPos);
		std::cout << "                    ";
		yCursorPos++;

		CursorOptions::SetCursorPosition(xCursorPosDraw, yCursorPos);
		std::cout << "      _             ";
		yCursorPos++;

		CursorOptions::SetCursorPosition(xCursorPosDraw, yCursorPos);
		std::cout << "       \\     _     ";
		yCursorPos++;

		CursorOptions::SetCursorPosition(xCursorPosDraw, yCursorPos);
		std::cout << "  (*>   \\   |_|    ";
		yCursorPos++;

		CursorOptions::SetCursorPosition(xCursorPosDraw, yCursorPos);
		std::cout << "         \\_/| |\\    " << "HEALTH: " << std::setfill('0') << std::setw(2) << GetHealth();
		yCursorPos++;

		CursorOptions::SetCursorPosition(xCursorPosDraw, yCursorPos);
		std::cout << "          \\ |_||   ";
		yCursorPos++;

		CursorOptions::SetCursorPosition(xCursorPosDraw, yCursorPos);
		std::cout << "            | |     ";
	}
}

void Wizard::DrawWarriorDamaged(bool isLeftSide, int yCursorPos, AttackState attackState)
{	

	if (isLeftSide)
	{
		if (attackState == AttackState::Crit)
		{
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), critAttackColor);
		}
		else if (attackState == AttackState::Miss)
		{
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), missAttackColor);
			damageReceived = 0;
		}

		CursorOptions::SetCursorPosition(0, yCursorPos);
		std::cout << "                                      ";
		yCursorPos++;

		CursorOptions::SetCursorPosition(0, yCursorPos);
		std::cout << "                             -" << std::setfill('0') << std::setw(2) << damageReceived << "          ";
		yCursorPos++;

		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), normalAttackColor);

		CursorOptions::SetCursorPosition(0, yCursorPos);
		std::cout << "                              _    _   ";
		yCursorPos++;

		CursorOptions::SetCursorPosition(0, yCursorPos);
		std::cout << "                             |_|  |    ";
		yCursorPos++;

		CursorOptions::SetCursorPosition(0, yCursorPos);
		std::cout << "             HEALTH: " << std::setfill('0') << std::setw(2) << GetHealth() << "     /| |\\ | ";
		yCursorPos++;

		CursorOptions::SetCursorPosition(0, yCursorPos);
		std::cout << "                            ||_| \\|   ";
		yCursorPos++;

		CursorOptions::SetCursorPosition(0, yCursorPos);
		std::cout << "                             | |  |    ";

	}
	else
	{
		if (attackState == AttackState::Crit)
		{
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), critAttackColor);
		}
		else if (attackState == AttackState::Miss)
		{
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), missAttackColor);
			damageReceived = 0;
		}

		CursorOptions::SetCursorPosition(xCursorPosDraw, yCursorPos);
		std::cout << "                    ";
		yCursorPos++;

		CursorOptions::SetCursorPosition(xCursorPosDraw, yCursorPos);
		std::cout << "           -" << std::setfill('0') << std::setw(2) << damageReceived << "          ";
		yCursorPos++;

		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), normalAttackColor);

		CursorOptions::SetCursorPosition(xCursorPosDraw, yCursorPos);
		std::cout << "        _    _      ";
		yCursorPos++;

		CursorOptions::SetCursorPosition(xCursorPosDraw, yCursorPos);
		std::cout << "         |  |_|     ";
		yCursorPos++;

		CursorOptions::SetCursorPosition(xCursorPosDraw, yCursorPos);
		std::cout << "         | /| |\\    " << "HEALTH: " << std::setfill('0') << std::setw(2) << GetHealth();
		yCursorPos++;

		CursorOptions::SetCursorPosition(xCursorPosDraw, yCursorPos);
		std::cout << "         |/ |_||    ";
		yCursorPos++;

		CursorOptions::SetCursorPosition(xCursorPosDraw, yCursorPos);
		std::cout << "         |  | |     ";
	}
}

AttackState Wizard::Attack(Warrior* warrior)
{
	AttackState attackState = AttackState::Normal;

	bool isCrit = CheckCritSuccess();
	SetDamage(this->normalDamage);

	if (isCrit)
	{
		attackState = AttackState::Crit;
		SetDamage(GetDamage() * this->critMultiplier);		
	}
	
	Warrior::Attack(warrior);

	return attackState;	
}