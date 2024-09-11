#pragma once	//ME FALTABA PRAGMA ONCE
#include <iostream>


class Warrior
{
	protected:

		std::string name;
		std::string warriorClass;		
		int damage;		
		int health;

		void SetName(std::string name);
		void SetWarriorClass(std::string warriorClass);
		void SetDamage(int damage);
		void SetHealth(int health);

		virtual void ReceiveDamage(int damage);	//Por que no se puede protegido?

	public:

		Warrior();
		virtual ~Warrior();	//si es virtual puro ( = 0 ) es necesario override.

		std::string GetName();
		std::string GetWarriorClass();
		int GetDamage();
		virtual int GetHealth();		

		virtual void ShowStatistics();	//si es virtual comun no es obligatorio override.
		virtual bool Attack(Warrior* warrior);
		




};
