#include <thread>
#include <chrono>
#include <iomanip>
#include "Warrior.h"
#include "CursorOptions.h"

Warrior::Warrior()
{
	this->name = "";
	this->warriorType = WarriorType::None;
	this->damage = 0;
	this->health = 0;
}

Warrior::~Warrior() {};

std::string Warrior::GetName() 
{ 
	return this->name; 
}

WarriorType Warrior::GetWarriorType()
{
	return this->warriorType;
}

int Warrior::GetDamage() 
{ 
	return this->damage; 
}

int Warrior::GetHealth()
{
	return this->health;
}

bool Warrior::GetDisplayDeadState()
{
	return this->displayDeadState;
}

void Warrior::SetDamage(int damage)
{
	this->damage = damage > 0 ? damage : 0;
}

void Warrior::SetHealth(int health)
{
	if (health < 0)
	{
		health = 0;
	}
	else if (health > 99)
	{
		health = 99;
	}

	this->health = health;
	
}

void Warrior::SetDisplayDeadState(bool state)	//o enable sin parametro que solo lo haga true?
{
	this->displayDeadState = state;
}

void Warrior::ReceiveDamage(int damage) 
{
	this->health = damage > this->health ? 0 : this->health - damage;
	this->damageReceived = damage;
}

void Warrior::ShowStatistics() 
{
	std::cout << "Nombre: " << this->name << std::endl;
	std::cout << "Danio: " << this->damage << std::endl;
	std::cout << "Salud: " << this->health << std::endl << std::endl;

}

void Warrior::DrawWarriorIdle(bool isLeftSide, int yCursorPos){}

void Warrior::DrawWarriorAttack(bool isLeftSide, int yCursorPos){}

void Warrior::DrawWarriorDamaged(bool isLeftSide, int yCursorPos, AttackState attackState){}

void Warrior::DrawWarriorDead(bool isLeftSide, int yCursorPos)
{
	if (isLeftSide)
	{
		CursorOptions::SetCursorPosition(0, yCursorPos);
		std::cout << "             ";
		yCursorPos++;

		CursorOptions::SetCursorPosition(0, yCursorPos);
		std::cout << "             ";
		yCursorPos++;

		CursorOptions::SetCursorPosition(0, yCursorPos);
		std::cout << "             ";
		yCursorPos++;

		CursorOptions::SetCursorPosition(0, yCursorPos);
		std::cout << "             ";
		yCursorPos++;

		CursorOptions::SetCursorPosition(0, yCursorPos);
		std::cout << "             HEALTH: " << std::setfill('0') << std::setw(2) << GetHealth();
		yCursorPos++;

		CursorOptions::SetCursorPosition(0, yCursorPos);
		std::cout << "                             _________  ";
		yCursorPos++;

		CursorOptions::SetCursorPosition(0, yCursorPos);
		std::cout << "                             __|___|__| ";
	}
	else
	{
		CursorOptions::SetCursorPosition(xCursorPosDraw, yCursorPos);
		std::cout << "             ";
		yCursorPos++;

		CursorOptions::SetCursorPosition(xCursorPosDraw, yCursorPos);
		std::cout << "             ";
		yCursorPos++;

		CursorOptions::SetCursorPosition(xCursorPosDraw, yCursorPos);
		std::cout << "             ";
		yCursorPos++;

		CursorOptions::SetCursorPosition(xCursorPosDraw, yCursorPos);
		std::cout << "             ";
		yCursorPos++;

		CursorOptions::SetCursorPosition(xCursorPosDraw, yCursorPos);
		std::cout << "                " << "   HEALTH: " << std::setfill('0') << std::setw(2) << GetHealth();
		yCursorPos++;

		CursorOptions::SetCursorPosition(xCursorPosDraw, yCursorPos);
		std::cout << "  _________  ";
		yCursorPos++;

		CursorOptions::SetCursorPosition(xCursorPosDraw, yCursorPos);
		std::cout << " |__|___|__  ";
	}
}

AttackState Warrior::Attack(Warrior* warrior)
{
	warrior->ReceiveDamage(this->damage);
	return AttackState::Normal;
}

Warrior Warrior::operator+(const Warrior& warrior) const
{
	Warrior result = *this;
	result.name += warrior.name;
	result.damage += warrior.damage;
	result.health += warrior.health;

	return result;
}


