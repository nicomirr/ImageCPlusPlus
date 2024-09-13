#include <thread>
#include <chrono>
#include "Tank.h"
#include "RandomGen.h"


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
	this->shield = shield > 0 ? shield : 0;
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

		std::cout << "Escudo de " << this->name << " daniado!" << std::endl << std::endl;
		std::this_thread::sleep_for(std::chrono::seconds(2));
		std::cout << "Puntos de vida restantes en escudo: " << this->shield << "." << std::endl << std::endl;
		std::this_thread::sleep_for(std::chrono::seconds(2));

	}
	
	if (shield <= 0 && !shieldDestroyed)
	{
		std::cout << "Escudo de " << this->name << " destruido!" << std::endl;
		std::this_thread::sleep_for(std::chrono::seconds(2));
		shieldDestroyed = true;		
	}
		
	SetHealth(damage > GetHealth() ? 0 : GetHealth() - damage);

}

void Tank::ShowStatistics()
{
	std::cout << "Nombre: " << this->name << std::endl;
	std::cout << "Danio: " << GetDamage() << std::endl;
	std::cout << "Escudo: " << this->shield << std::endl;
	std::cout << "Salud: " << GetHealth()  << std::endl;

	std::this_thread::sleep_for(std::chrono::seconds(3));
}

