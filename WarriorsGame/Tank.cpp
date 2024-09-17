#include <thread>
#include <chrono>
#include <iomanip>
#include "Tank.h"
#include "RandomGen.h"
#include "CursorOptions.h"


Tank::Tank(int minPossibleDamage, int maxPossibleDamage, int minPossibleHealth, int maxPossibleHealth,
			int minPossibleShield, int maxPossibleShield)
{
	RandomGen* randomGen = new RandomGen();
	
	this->name = "Tanque";
	this->warriorType = WarriorType::Tank;
	SetDamage(randomGen->RandomRange(minPossibleDamage, maxPossibleDamage));
	SetHealth(randomGen->RandomRange(minPossibleHealth, maxPossibleHealth));
	SetShield(randomGen->RandomRange(minPossibleShield, maxPossibleShield));
	shieldDestroyed = false;

	std::cout << "Tanque " << this->name << " creado." << std::endl;

	ShowStatistics();

	delete randomGen;
}

Tank::~Tank()
{
	std::cout << "Tanque " << this->name << " destruido." << std::endl;;
}


int Tank::GetShield()
{
	return this->shield;
}


void Tank :: SetShield(int shield)
{
	if (shield < 0)
	{
		shield = 0;
	}
	else if (shield > 99)
	{
		shield = 99;
	}

	this->shield = shield;
}

int Tank::UseShieldAgainstAttack(int damage)
{
	int directDamageDealth = damage > this->shield ? damage - shield : 0;

	SetShield(this->shield - damage);
		
	return directDamageDealth;
}


void Tank::ReceiveDamage(int damage)	//cambiar el log a tanque bloqueo y no recibio daño en la clase game cpp?
{
	if (shield > 0)
	{
		damage = UseShieldAgainstAttack(damage);

		//std::cout << "Escudo de " << this->name << " daniado!" << std::endl << std::endl;
		
		//std::cout << "Puntos de vida restantes en escudo: " << this->shield << "." << std::endl << std::endl;
		

	}
	
	if (shield <= 0 && !shieldDestroyed)
	{
		//std::cout << "Escudo de " << this->name << " destruido!" << std::endl;
		
		shieldDestroyed = true;		
	}
		
	SetHealth(damage > GetHealth() ? 0 : GetHealth() - damage);
	
	this->damageReceived = damage;
}

void Tank::ShowStatistics()
{
	std::cout << "Nombre: " << this->name << std::endl;
	std::cout << "Danio: " << GetDamage() << std::endl;
	std::cout << "Escudo: " << this->shield << std::endl;
	std::cout << "Salud: " << GetHealth()  << std::endl;

}

void Tank::DrawWarriorIdle(bool isLeftSide, int yCursorPos)
{
	if (GetHealth() <= 0)
	{
		DrawWarriorDead(isLeftSide, yCursorPos);
		return;
	}

	if (isLeftSide)
	{

		if (GetShield() > 0)
		{
			CursorOptions::SetCursorPosition(0, yCursorPos);
			std::cout << "                                       ";
			yCursorPos++;

			CursorOptions::SetCursorPosition(0, yCursorPos);
			std::cout << "                                       ";
			yCursorPos++;

			CursorOptions::SetCursorPosition(0, yCursorPos);
			std::cout << "                              _   |    ";
			yCursorPos++;

			CursorOptions::SetCursorPosition(0, yCursorPos);
			std::cout << "                            _|_| _|_   ";
			yCursorPos++;

			CursorOptions::SetCursorPosition(0, yCursorPos);
			std::cout << "             HEALTH: " << std::setfill('0') << std::setw(2) << GetHealth() << "    (_) |__| ";
			yCursorPos++;

			CursorOptions::SetCursorPosition(0, yCursorPos);
			std::cout << "             SHIELD: " << std::setfill('0') << std::setw(2) << GetShield() << "      |_| ";
			yCursorPos++;

			CursorOptions::SetCursorPosition(0, yCursorPos);
			std::cout << "                             | |       ";
		}
		else
		{
			CursorOptions::SetCursorPosition(0, yCursorPos);
			std::cout << "                                       ";
			yCursorPos++;

			CursorOptions::SetCursorPosition(0, yCursorPos);
			std::cout << "                                       ";
			yCursorPos++;

			CursorOptions::SetCursorPosition(0, yCursorPos);
			std::cout << "                              _   |    ";
			yCursorPos++;

			CursorOptions::SetCursorPosition(0, yCursorPos);
			std::cout << "                             |_| _|_   ";
			yCursorPos++;

			CursorOptions::SetCursorPosition(0, yCursorPos);
			std::cout << "             HEALTH: " << std::setfill('0') << std::setw(2) << GetHealth() << "      | |__| ";
			yCursorPos++;

			CursorOptions::SetCursorPosition(0, yCursorPos);
			std::cout << "             SHIELD: " << std::setfill('0') << std::setw(2) << GetShield() << "      |_| ";
			yCursorPos++;

			CursorOptions::SetCursorPosition(0, yCursorPos);
			std::cout << "                             | |       ";
		}
		
		
	}
	else
	{
		if (GetShield() > 0)
		{
			CursorOptions::SetCursorPosition(xCursorPosDraw, yCursorPos);
			std::cout << "                    ";
			yCursorPos++;

			CursorOptions::SetCursorPosition(xCursorPosDraw, yCursorPos);
			std::cout << "                    ";
			yCursorPos++;

			CursorOptions::SetCursorPosition(xCursorPosDraw, yCursorPos);
			std::cout << "         |   _      ";
			yCursorPos++;

			CursorOptions::SetCursorPosition(xCursorPosDraw, yCursorPos);
			std::cout << "        _|_ |_|_    ";
			yCursorPos++;

			CursorOptions::SetCursorPosition(xCursorPosDraw, yCursorPos);
			std::cout << "         |__| (_)   " << "HEALTH: " << std::setfill('0') << std::setw(2) << GetHealth();
			yCursorPos++;

			CursorOptions::SetCursorPosition(xCursorPosDraw, yCursorPos);
			std::cout << "            |_|     SHIELD: " << std::setfill('0') << std::setw(2) << GetShield();
			yCursorPos++;

			CursorOptions::SetCursorPosition(xCursorPosDraw, yCursorPos);
			std::cout << "            | |     ";
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
			std::cout << "         |   _      ";
			yCursorPos++;

			CursorOptions::SetCursorPosition(xCursorPosDraw, yCursorPos);
			std::cout << "        _|_ |_|     ";
			yCursorPos++;

			CursorOptions::SetCursorPosition(xCursorPosDraw, yCursorPos);
			std::cout << "         |__| |     " << "HEALTH: " << std::setfill('0') << std::setw(2) << GetHealth();
			yCursorPos++;

			CursorOptions::SetCursorPosition(xCursorPosDraw, yCursorPos);
			std::cout << "            |_|     SHIELD: " << std::setfill('0') << std::setw(2) << GetShield();
			yCursorPos++;

			CursorOptions::SetCursorPosition(xCursorPosDraw, yCursorPos);
			std::cout << "            | |     ";
		}
		
	}
}

void Tank::DrawWarriorAttack(bool isLeftSide, int yCursorPos)
{
	if (isLeftSide)
	{
		if (GetShield() > 0)
		{
			CursorOptions::SetCursorPosition(0, yCursorPos);
			std::cout << "                                        ";
			yCursorPos++;

			CursorOptions::SetCursorPosition(0, yCursorPos);
			std::cout << "                                        ";
			yCursorPos++;

			CursorOptions::SetCursorPosition(0, yCursorPos);
			std::cout << "                              _     /   ";
			yCursorPos++;

			CursorOptions::SetCursorPosition(0, yCursorPos);
			std::cout << "                            _|_|  _/_   ";
			yCursorPos++;

			CursorOptions::SetCursorPosition(0, yCursorPos);
			std::cout << "             HEALTH: " << std::setfill('0') << std::setw(2) << GetHealth() << "    (_) |__/ ";
			yCursorPos++;

			CursorOptions::SetCursorPosition(0, yCursorPos);
			std::cout << "             SHIELD: " << std::setfill('0') << std::setw(2) << GetShield() << "      |_| ";
			yCursorPos++;

			CursorOptions::SetCursorPosition(0, yCursorPos);
			std::cout << "                             | |        ";
		}
		else
		{
			CursorOptions::SetCursorPosition(0, yCursorPos);
			std::cout << "                                        ";
			yCursorPos++;

			CursorOptions::SetCursorPosition(0, yCursorPos);
			std::cout << "                                        ";
			yCursorPos++;

			CursorOptions::SetCursorPosition(0, yCursorPos);
			std::cout << "                              _     /   ";
			yCursorPos++;

			CursorOptions::SetCursorPosition(0, yCursorPos);
			std::cout << "                             |_|  _/_   ";
			yCursorPos++;

			CursorOptions::SetCursorPosition(0, yCursorPos);
			std::cout << "             HEALTH: " << std::setfill('0') << std::setw(2) << GetHealth() << "      | |__/ ";
			yCursorPos++;

			CursorOptions::SetCursorPosition(0, yCursorPos);
			std::cout << "             SHIELD: " << std::setfill('0') << std::setw(2) << GetShield() << "      |_| ";
			yCursorPos++;

			CursorOptions::SetCursorPosition(0, yCursorPos);
			std::cout << "                             | |        ";
		}
		
	}
	else
	{
		if (GetShield() > 0)
		{
			CursorOptions::SetCursorPosition(xCursorPosDraw, yCursorPos);
			std::cout << "                   ";
			yCursorPos++;

			CursorOptions::SetCursorPosition(xCursorPosDraw, yCursorPos);
			std::cout << "                   ";
			yCursorPos++;

			CursorOptions::SetCursorPosition(xCursorPosDraw, yCursorPos);
			std::cout << "       \\     _    ";
			yCursorPos++;

			CursorOptions::SetCursorPosition(xCursorPosDraw, yCursorPos);
			std::cout << "       _\\_  |_|_  ";
			yCursorPos++;

			CursorOptions::SetCursorPosition(xCursorPosDraw, yCursorPos);
			std::cout << "         \\__| (_)   " << "HEALTH: " << std::setfill('0') << std::setw(2) << GetHealth();
			yCursorPos++;

			CursorOptions::SetCursorPosition(xCursorPosDraw, yCursorPos);
			std::cout << "            |_|     SHIELD: " << std::setfill('0') << std::setw(2) << GetShield();
			yCursorPos++;

			CursorOptions::SetCursorPosition(xCursorPosDraw, yCursorPos);
			std::cout << "            | |    ";
		}
		else
		{
			CursorOptions::SetCursorPosition(xCursorPosDraw, yCursorPos);
			std::cout << "                   ";
			yCursorPos++;

			CursorOptions::SetCursorPosition(xCursorPosDraw, yCursorPos);
			std::cout << "                   ";
			yCursorPos++;

			CursorOptions::SetCursorPosition(xCursorPosDraw, yCursorPos);
			std::cout << "       \\     _    ";
			yCursorPos++;

			CursorOptions::SetCursorPosition(xCursorPosDraw, yCursorPos);
			std::cout << "       _\\_  |_|     ";
			yCursorPos++;

			CursorOptions::SetCursorPosition(xCursorPosDraw, yCursorPos);
			std::cout << "         \\__| |     " << "HEALTH: " << std::setfill('0') << std::setw(2) << GetHealth();
			yCursorPos++;

			CursorOptions::SetCursorPosition(xCursorPosDraw, yCursorPos);
			std::cout << "            |_|     SHIELD: " << std::setfill('0') << std::setw(2) << GetShield();
			yCursorPos++;

			CursorOptions::SetCursorPosition(xCursorPosDraw, yCursorPos);
			std::cout << "            | |    ";
		}

		
	}	
}

void Tank::DrawWarriorDamaged(bool isLeftSide, int yCursorPos, AttackState attackState)
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

		if (GetShield() > 0)
		{
			CursorOptions::SetCursorPosition(0, yCursorPos);
			std::cout << "                                       ";
			yCursorPos++;

			CursorOptions::SetCursorPosition(0, yCursorPos);
			std::cout << "                             -" << std::setfill('0') << std::setw(2) << damageReceived << "          ";
			yCursorPos++;

			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), normalAttackColor);

			CursorOptions::SetCursorPosition(0, yCursorPos);
			std::cout << "                              _   |    ";
			yCursorPos++;

			CursorOptions::SetCursorPosition(0, yCursorPos);
			std::cout << "                            _|_| _|_   ";
			yCursorPos++;

			CursorOptions::SetCursorPosition(0, yCursorPos);
			std::cout << "             HEALTH: " << std::setfill('0') << std::setw(2) << GetHealth() << "    (_) |__| ";
			yCursorPos++;

			CursorOptions::SetCursorPosition(0, yCursorPos);
			std::cout << "             SHIELD: " << std::setfill('0') << std::setw(2) << GetShield() << "      |_| ";
			yCursorPos++;

			CursorOptions::SetCursorPosition(0, yCursorPos);
			std::cout << "                             | |       ";
		}
		else
		{
			CursorOptions::SetCursorPosition(0, yCursorPos);
			std::cout << "                                       ";
			yCursorPos++;

			CursorOptions::SetCursorPosition(0, yCursorPos);
			std::cout << "                             -" << std::setfill('0') << std::setw(2) << damageReceived << "          ";
			yCursorPos++;

			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), normalAttackColor);

			CursorOptions::SetCursorPosition(0, yCursorPos);
			std::cout << "                              _   |    ";
			yCursorPos++;

			CursorOptions::SetCursorPosition(0, yCursorPos);
			std::cout << "                             |_| _|_   ";
			yCursorPos++;

			CursorOptions::SetCursorPosition(0, yCursorPos);
			std::cout << "             HEALTH: " << std::setfill('0') << std::setw(2) << GetHealth() << "      | |__| ";
			yCursorPos++;

			CursorOptions::SetCursorPosition(0, yCursorPos);
			std::cout << "             SHIELD: " << std::setfill('0') << std::setw(2) << GetShield() << "      |_| ";
			yCursorPos++;

			CursorOptions::SetCursorPosition(0, yCursorPos);
			std::cout << "                             | |       ";
		}

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

		if (shield > 0)
		{
			CursorOptions::SetCursorPosition(xCursorPosDraw, yCursorPos);
			std::cout << "                    ";
			yCursorPos++;

			CursorOptions::SetCursorPosition(xCursorPosDraw, yCursorPos);
			std::cout << "           -" << std::setfill('0') << std::setw(2) << damageReceived << "          ";
			yCursorPos++;

			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), normalAttackColor);

			CursorOptions::SetCursorPosition(xCursorPosDraw, yCursorPos);
			std::cout << "         |   _      ";
			yCursorPos++;

			CursorOptions::SetCursorPosition(xCursorPosDraw, yCursorPos);
			std::cout << "        _|_ |_|_    ";
			yCursorPos++;

			CursorOptions::SetCursorPosition(xCursorPosDraw, yCursorPos);
			std::cout << "         |__| (_)   " << "HEALTH: " << std::setfill('0') << std::setw(2) << GetHealth();
			yCursorPos++;

			CursorOptions::SetCursorPosition(xCursorPosDraw, yCursorPos);
			std::cout << "            |_|     SHIELD: " << std::setfill('0') << std::setw(2) << GetShield();
			yCursorPos++;

			CursorOptions::SetCursorPosition(xCursorPosDraw, yCursorPos);
			std::cout << "            | |     ";
		}
		else
		{
			CursorOptions::SetCursorPosition(xCursorPosDraw, yCursorPos);
			std::cout << "                    ";
			yCursorPos++;

			CursorOptions::SetCursorPosition(xCursorPosDraw, yCursorPos);
			std::cout << "           -" << std::setfill('0') << std::setw(2) << damageReceived << "          ";
			yCursorPos++;

			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), normalAttackColor);

			CursorOptions::SetCursorPosition(xCursorPosDraw, yCursorPos);
			std::cout << "         |   _      ";
			yCursorPos++;

			CursorOptions::SetCursorPosition(xCursorPosDraw, yCursorPos);
			std::cout << "        _|_ |_|     ";
			yCursorPos++;

			CursorOptions::SetCursorPosition(xCursorPosDraw, yCursorPos);
			std::cout << "         |__| |     " << "HEALTH: " << std::setfill('0') << std::setw(2) << GetHealth();
			yCursorPos++;

			CursorOptions::SetCursorPosition(xCursorPosDraw, yCursorPos);
			std::cout << "            |_|     SHIELD: " << std::setfill('0') << std::setw(2) << GetShield();
			yCursorPos++;

			CursorOptions::SetCursorPosition(xCursorPosDraw, yCursorPos);
			std::cout << "            | |     ";
		}

		
	}
}

