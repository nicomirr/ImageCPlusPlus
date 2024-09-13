#pragma once	//ME FALTABA PRAGMA ONCE
#include <iostream>


//CREAR ENUM CLASS Y UN ATRIBUTO ENUM EN LUGAR DE STRING

//CAMBIAR LOGICA DEL MAIN

enum class WarriorType
{
	None = -1,
	Tank,
	Archer,
	Wizard,
	End = 3,
};


class Warrior
{
	private:

		int damage;		
		int health;

	protected:

		std::string name;		
		WarriorType warriorType;
				
		void SetDamage(int damage);
		void SetHealth(int health);

		virtual void ReceiveDamage(int damage);	//Por que no se puede protegido?

	public:

		Warrior();
		virtual ~Warrior();	//si es virtual puro ( = 0 ) es necesario override.

		std::string GetName();
		WarriorType GetWarriorType();
		int GetDamage();
		virtual int GetHealth();		

		virtual void ShowStatistics();	//si es virtual comun no es obligatorio override.
		virtual bool Attack(Warrior* warrior);
		
		void operator+(const Warrior& warrior);
		
};
