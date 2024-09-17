#pragma once	//ME FALTABA PRAGMA ONCE
#include <iostream>


//CREAR ENUM CLASS Y UN ATRIBUTO ENUM EN LUGAR DE STRING

//CAMBIAR LOGICA DEL MAIN

enum class AttackState
{
	None = -1,
	Normal,
	Crit,
	Miss,
	End = 3,
};

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

		bool displayDeadState = false;


	protected:

		int normalAttackColor = 7;
		int missAttackColor = 11;
		int critAttackColor = 12;

		int damageReceived;
		int xCursorPosDraw = 65;

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
		bool GetDisplayDeadState();

		void SetDisplayDeadState(bool state);

		virtual void ShowStatistics();	//si es virtual comun no es obligatorio override.

		virtual void DrawWarriorIdle(bool isLeftSide, int yCursorPos);
		virtual void DrawWarriorAttack(bool isLeftSide, int yCursorPos);
		virtual void DrawWarriorDamaged(bool isLeftSide, int yCursorPos, 
			AttackState attackState);

		void DrawWarriorDead(bool isLeftSide, int yCursorPos);

		virtual AttackState Attack(Warrior* warrior);
		
		Warrior operator+(const Warrior& warrior) const;
		
};
