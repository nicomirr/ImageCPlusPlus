#include <thread>
#include <chrono>
#include "Warrior.h"

Warrior::Warrior()
{
	this->name = "Null";
	this->warriorClass = "Null";	
	this->damage = 0;
	this->health = 0;
}

Warrior::~Warrior() {};

std::string Warrior::GetName() 
{ 
	return this->name; 
}

std::string Warrior::GetWarriorClass()
{
	return this->warriorClass;
}

int Warrior::GetDamage() 
{ 
	return this->damage; 
}

int Warrior::GetHealth()
{
	return this->health;
}

void Warrior::SetName(std::string name)
{
	this->name = name;
}

void Warrior::SetWarriorClass(std::string warriorClass)
{
	this->warriorClass = warriorClass;
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
	std::cout << "Clase: " << this->warriorClass << std::endl;
	std::cout << "Danio: " << this->damage << std::endl;
	std::cout << "Salud: " << this->health << std::endl << std::endl;

	std::this_thread::sleep_for(std::chrono::seconds(3));
}

bool Warrior::Attack(Warrior* warrior)
{
	warrior->ReceiveDamage(this->damage);
	return true;
}


