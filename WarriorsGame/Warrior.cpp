#include <thread>
#include <chrono>
#include "Warrior.h"

Warrior::Warrior()
{
	this->name = "Null";
	this->warriorType = WarriorType::None;
	this->damage = -1;
	this->health = -1;
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

void Warrior::SetDamage(int damage)
{
	this->damage = damage > 0 ? damage : 0;
}

void Warrior::SetHealth(int health)
{
	this->health = health > 1 ? health : 1;
}

void Warrior::ReceiveDamage(int damage) 
{
	this->health = damage > this->health ? 0 : this->health - damage;
}

void Warrior::ShowStatistics() 
{
	std::cout << "Nombre: " << this->name << std::endl;
	std::cout << "Danio: " << this->damage << std::endl;
	std::cout << "Salud: " << this->health << std::endl << std::endl;

	std::this_thread::sleep_for(std::chrono::seconds(3));
}

bool Warrior::Attack(Warrior* warrior)
{
	warrior->ReceiveDamage(this->damage);
	return true;
}

void Warrior::operator+(const Warrior& warrior)
{
	this->name += warrior.name;
	this->damage += warrior.damage;
	this->health += warrior.health;
}


