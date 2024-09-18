#include "Archer.h"


Archer::Archer(int minPossibleDamage, int maxPossibleDamage, int minPossibleHealth, int maxPossibleHealth)
{
	RandomGen* randomGen = new RandomGen();

	this->name = "Arquero";
	this->warriorType = WarriorType::Archer;
		
	SetDamage(randomGen->RandomRange(minPossibleDamage, maxPossibleDamage));
	SetHealth(randomGen->RandomRange(minPossibleHealth, maxPossibleHealth));

	this->normalDamage = GetDamage();
	this->damageMultiplier = 2;

	std::cout << "Arquero " << this->name << " creado." << std::endl;
	ShowStatistics();

	delete randomGen;

}

Archer::~Archer()
{
	std::cout << "Arquero " << this->name << " destruido." << std::endl;
}

bool Archer::CheckAttackSuccess()
{
	int randSuccessChance = rand() % 2;

	return randSuccessChance == 1 ? true : false;
}

void Archer::DrawWarriorIdle(bool isLeftSide, int yCursorPos)
{
	if (GetHealth() <= 0)
	{
		DrawWarriorDead(isLeftSide, yCursorPos);
		return;
	}

	if (isLeftSide)
	{
		CursorOptions::SetCursorPosition(0, yCursorPos);
		std::cout << "                                     ";
		yCursorPos++;

		CursorOptions::SetCursorPosition(0, yCursorPos);
		std::cout << "                                     ";
		yCursorPos++;

		CursorOptions::SetCursorPosition(0, yCursorPos);
		std::cout << "                              _      ";
		yCursorPos++;

		CursorOptions::SetCursorPosition(0, yCursorPos);
		std::cout << "                             |_| |\\ ";
		yCursorPos++;

		CursorOptions::SetCursorPosition(0, yCursorPos);
		std::cout << "             HEALTH: " << std::setfill('0') << std::setw(2) << GetHealth() << "      | |_|| ";
		yCursorPos++;

		CursorOptions::SetCursorPosition(0, yCursorPos);
		std::cout << "                             |_| |/  ";
		yCursorPos++;

		CursorOptions::SetCursorPosition(0, yCursorPos);
		std::cout << "                             | |     ";
		yCursorPos++;

	}
	else
	{
		CursorOptions::SetCursorPosition(xCursorPosDraw, yCursorPos);
		std::cout << "                  ";
		yCursorPos++;
		
		CursorOptions::SetCursorPosition(xCursorPosDraw, yCursorPos);
		std::cout << "                  ";
		yCursorPos++;

		CursorOptions::SetCursorPosition(xCursorPosDraw, yCursorPos);
		std::cout << "             _    ";
		yCursorPos++;

		CursorOptions::SetCursorPosition(xCursorPosDraw, yCursorPos);
		std::cout << "         /| |_|   ";
		yCursorPos++;

		CursorOptions::SetCursorPosition(xCursorPosDraw, yCursorPos);
		std::cout << "         ||_|_|    " << "HEALTH: " << std::setfill('0') << std::setw(2) << GetHealth();
		yCursorPos++;

		CursorOptions::SetCursorPosition(xCursorPosDraw, yCursorPos);
		std::cout << "         \\| |_|  ";
		yCursorPos++;

		CursorOptions::SetCursorPosition(xCursorPosDraw, yCursorPos);
		std::cout << "            | |   ";
	}
}

void Archer::DrawWarriorAttack(bool isLeftSide, int yCursorPos)
{
	if (isLeftSide)
	{
		CursorOptions::SetCursorPosition(0, yCursorPos);
		std::cout << "                                        ";
		yCursorPos++;

		CursorOptions::SetCursorPosition(0, yCursorPos);
		std::cout << "                                        ";
		yCursorPos++;

		CursorOptions::SetCursorPosition(0, yCursorPos);
		std::cout << "                              _          ";
		yCursorPos++;

		CursorOptions::SetCursorPosition(0, yCursorPos);
		std::cout << "                             |_| |\\     ";
		yCursorPos++;

		CursorOptions::SetCursorPosition(0, yCursorPos);
		std::cout << "             HEALTH: " << std::setfill('0') << std::setw(2) << GetHealth() << "      | |_|| --->";
		yCursorPos++;

		CursorOptions::SetCursorPosition(0, yCursorPos);
		std::cout << "                             |_| |/      ";
		yCursorPos++;

		CursorOptions::SetCursorPosition(0, yCursorPos);
		std::cout << "                             | |         ";
	}
	else
	{
		CursorOptions::SetCursorPosition(xCursorPosDraw, yCursorPos);
		std::cout << "                 ";
		yCursorPos++;
		
		CursorOptions::SetCursorPosition(xCursorPosDraw, yCursorPos);
		std::cout << "                 ";
		yCursorPos++;

		CursorOptions::SetCursorPosition(xCursorPosDraw, yCursorPos);
		std::cout << "             _   ";
		yCursorPos++;

		CursorOptions::SetCursorPosition(xCursorPosDraw, yCursorPos);
		std::cout << "         /| |_|  ";
		yCursorPos++;

		CursorOptions::SetCursorPosition(xCursorPosDraw, yCursorPos);
		std::cout << "    <--- ||_|_|      " << "HEALTH: " << std::setfill('0') << std::setw(2) << GetHealth();
		yCursorPos++;

		CursorOptions::SetCursorPosition(xCursorPosDraw, yCursorPos);
		std::cout << "         \\| |_| ";
		yCursorPos++;

		CursorOptions::SetCursorPosition(xCursorPosDraw, yCursorPos);
		std::cout << "            | |  ";
	}
}

void Archer::DrawWarriorDamaged(bool isLeftSide, int yCursorPos, AttackState attackState)
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
		std::cout << "                                     ";
		yCursorPos++;

		CursorOptions::SetCursorPosition(0, yCursorPos);
		std::cout << "                             -" << std::setfill('0') << std::setw(2) << damageReceived << "          ";
		yCursorPos++;

		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), normalAttackColor);

		CursorOptions::SetCursorPosition(0, yCursorPos);
		std::cout << "                              _      ";
		yCursorPos++;

		CursorOptions::SetCursorPosition(0, yCursorPos);
		std::cout << "                             |_| |\\ ";
		yCursorPos++;

		CursorOptions::SetCursorPosition(0, yCursorPos);
		std::cout << "             HEALTH: " << std::setfill('0') << std::setw(2) << GetHealth() << "      | |_|| ";
		yCursorPos++;

		CursorOptions::SetCursorPosition(0, yCursorPos);
		std::cout << "                             |_| |/  ";
		yCursorPos++;

		CursorOptions::SetCursorPosition(0, yCursorPos);
		std::cout << "                             | |     ";
		yCursorPos++;

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
		std::cout << "                  ";
		yCursorPos++;

		CursorOptions::SetCursorPosition(xCursorPosDraw, yCursorPos);
		std::cout << "           -" << std::setfill('0') << std::setw(2) << damageReceived << "          ";
		yCursorPos++;

		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), normalAttackColor);

		CursorOptions::SetCursorPosition(xCursorPosDraw, yCursorPos);
		std::cout << "             _    ";
		yCursorPos++;

		CursorOptions::SetCursorPosition(xCursorPosDraw, yCursorPos);
		std::cout << "         /| |_|   ";
		yCursorPos++;

		CursorOptions::SetCursorPosition(xCursorPosDraw, yCursorPos);
		std::cout << "         ||_|_|    " << "HEALTH: " << std::setfill('0') << std::setw(2) << GetHealth();
		yCursorPos++;

		CursorOptions::SetCursorPosition(xCursorPosDraw, yCursorPos);
		std::cout << "         \\| |_|  ";
		yCursorPos++;

		CursorOptions::SetCursorPosition(xCursorPosDraw, yCursorPos);
		std::cout << "            | |   ";
	}
}


AttackState Archer::Attack(Warrior* warrior)
{
	AttackState attackState;
	bool isSuccessfulAttack = CheckAttackSuccess();

	if (isSuccessfulAttack)
	{
		attackState = AttackState::Normal;

		SetDamage(this->normalDamage);
		SetDamage(GetDamage() * damageMultiplier);

		Warrior::Attack(warrior);		
	}
	else
	{
		attackState = AttackState::Miss;

		SetDamage(0);
	}

	return attackState;
}

