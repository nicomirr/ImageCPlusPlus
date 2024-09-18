#include "Game.h"


int Game::drawingsCurrentHeight;

Warrior* Game::warriorGroups[TOTAL_GROUPS][WARRIORS_IN_GROUPS];

Game::Game(){ }

Game::~Game(){ }

void Game::InitGame()
{
	drawingsCurrentHeight = 0;
	srand(time(NULL));
}

void Game::ResetPointers()
{
	for (int group = 0; group < TOTAL_GROUPS; group++)
	{
		for (int warrior = 0; warrior < WARRIORS_IN_GROUPS; warrior++)
		{
			warriorGroups[group][warrior] = nullptr;
		}
	}
}

void Game::Play()
{
	InitGame();
	ResetPointers();
	Gameloop();
}

void Game::GenerateRandomWarriors()
{
	RandomGen* randomGen = new RandomGen();
	int totalClasses = static_cast<int>(WarriorType::End) - 1;
	int rand = -1;

	for (int group = 0; group < TOTAL_GROUPS; group++)
	{
		for (int warrior = 0; warrior < WARRIORS_IN_GROUPS; warrior++)
		{
			rand = randomGen->RandomRange(0, totalClasses);

			switch (rand)
			{
				case 0:

					warriorGroups[group][warrior] = new Tank(5, 10, 20, 30, 5, 10);
					break;

				case 1:

					warriorGroups[group][warrior] = new Archer(5, 10, 20, 30);
					break;

				case 2:

					warriorGroups[group][warrior] = new Wizard(5, 10, 20, 30);
					break;

				default:

					break;
			}
		}		
	}	

	delete randomGen;
	randomGen = nullptr;
}

void Game::DisplayGroups()
{

	for (int group = 0; group < TOTAL_GROUPS; group++)
	{
		Warrior warriorGroup;

		for (int warrior = 0; warrior < WARRIORS_IN_GROUPS; warrior++)
		{
			warriorGroup = warriorGroup + *warriorGroups[group][warrior];
		}

		std::cout << "Grupo " << group + 1 << std::endl;

		std::cout << warriorGroup.GetName() << std::endl;
		std::cout << warriorGroup.GetHealth() << std::endl;
		std::cout << warriorGroup.GetDamage() << std::endl;

		std::cin.get();

	}
}

void Game::Gameloop() 
{
	GenerateRandomWarriors();
	DisplayGroups();

	int firstAttackerGroup = rand() % TOTAL_GROUPS;
	bool inBattle = true;

	AttackState attackState = AttackState::None;	
	
    std::cout << "Comienza atacando el grupo " << firstAttackerGroup + 1 << "." << std::endl;
	system("cls");

	int aliveGroups = TOTAL_GROUPS;
	int winnerGroup = 0;
	int groupsThatHaveAttacked = 0;
	int remainingWarriorsCurrentGroup = 0;
	bool attackerOnLeft = true;

	while (inBattle)
	{
		winnerGroup = 0;
		groupsThatHaveAttacked = 0;

		for (int currentAttackingGroup = firstAttackerGroup; 
			currentAttackingGroup < TOTAL_GROUPS; currentAttackingGroup++)
		{
			drawingsCurrentHeight = 0;
			int defenderGroup = currentAttackingGroup == (TOTAL_GROUPS - 1) ? 0 : currentAttackingGroup + 1;

			for (int currentWarrior = 0; currentWarrior < WARRIORS_IN_GROUPS; currentWarrior++)
			{
				Draw(warriorGroups[currentAttackingGroup][currentWarrior], warriorGroups[defenderGroup][currentWarrior], attackerOnLeft,
					BattleMoment::IdleMoment, attackState, false);
								
				drawingsCurrentHeight += DRAWINGS_SPACING;
			}

			std::cin.get();
			system("cls");

			drawingsCurrentHeight = 0;

			for (int currentWarrior = 0; currentWarrior < WARRIORS_IN_GROUPS; currentWarrior++)
			{				
				if (warriorGroups[currentAttackingGroup][currentWarrior]->GetHealth() > 0)
				{					
					if (warriorGroups[defenderGroup][currentWarrior]->GetHealth() > 0)
					{
						Draw(warriorGroups[currentAttackingGroup][currentWarrior], warriorGroups[defenderGroup][currentWarrior], attackerOnLeft,
							BattleMoment::AttackMoment, attackState, false);
					}
					else if (warriorGroups[defenderGroup][currentWarrior]->GetHealth() <= 0)
					{
						Draw(warriorGroups[currentAttackingGroup][currentWarrior], warriorGroups[defenderGroup][currentWarrior], attackerOnLeft,
							BattleMoment::IdleMoment, attackState, false);
					}

					attackState = warriorGroups[currentAttackingGroup][currentWarrior]->
						Attack(warriorGroups[defenderGroup][currentWarrior]);

					if (!warriorGroups[defenderGroup][currentWarrior]->GetDisplayDeadState())
					{
						Draw(warriorGroups[currentAttackingGroup][currentWarrior], warriorGroups[defenderGroup][currentWarrior], attackerOnLeft,
							BattleMoment::AttackMoment, attackState, true);

						if (warriorGroups[defenderGroup][currentWarrior]->GetHealth() <= 0)
						{
							groupPoints[currentAttackingGroup]++;
							warriorGroups[defenderGroup][currentWarrior]->SetDisplayDeadState(true);
						}
					}					
										
				}
				else
				{
					Draw(warriorGroups[currentAttackingGroup][currentWarrior], warriorGroups[defenderGroup][currentWarrior], attackerOnLeft,
						BattleMoment::IdleMoment, attackState, false);
				}
								
				drawingsCurrentHeight += DRAWINGS_SPACING;
			}
			
			attackerOnLeft = !attackerOnLeft;

			std::cin.get();
			system("cls");
			
			winnerGroup = currentAttackingGroup + 1;
			if (groupPoints[currentAttackingGroup] == WARRIORS_IN_GROUPS - 1)
			{
				inBattle = false;
				break;

			}

			groupsThatHaveAttacked++;

			if (groupsThatHaveAttacked < TOTAL_GROUPS && currentAttackingGroup == (TOTAL_GROUPS - 1))
			{
				currentAttackingGroup = -1;
			}								
			
			if (groupsThatHaveAttacked == TOTAL_GROUPS) break;
		}
		
	}
						
	std::cout << "Ha ganado el grupo " << winnerGroup << "." << std::endl;

	std::cin.get();

	//DeletePointers();	
	
	system("cls");
	int input = 0;

	std::cout << "Simular nueva batalla?" << std::endl;
	std::cout << "1. Si." << std::endl;
	std::cout << "2. No." << std::endl;
	std::cin >> input;
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

	if (input == 1)
	{
		ResetPointers();
		Gameloop();
	}
		
}

void Game::Draw(Warrior* warriorAttacker, Warrior* warriorDefender, bool attackerIsOnLeft, BattleMoment battleMoment, AttackState attackState, bool showDamage)
{

	if (battleMoment == BattleMoment::IdleMoment)
	{
		warriorAttacker->DrawWarriorIdle(attackerIsOnLeft, drawingsCurrentHeight);
		warriorDefender->DrawWarriorIdle(!attackerIsOnLeft, drawingsCurrentHeight);
				
	}
	else if (battleMoment == BattleMoment::AttackMoment)
	{
		warriorAttacker->DrawWarriorAttack(attackerIsOnLeft, drawingsCurrentHeight);

		if (!warriorDefender->GetDisplayDeadState() && showDamage)
		{
			warriorDefender->DrawWarriorDamaged(!attackerIsOnLeft, drawingsCurrentHeight, attackState);
		}
		else
		{
			warriorDefender->DrawWarriorIdle(!attackerIsOnLeft, drawingsCurrentHeight);
		}

	}

}

//void Game::DeletePointers()
//{
//	for (int i = 0; i < TOTAL_GROUPS; i++)
//	{
//		for (int j = 0; j < WARRIORS_IN_GROUPS; j++)
//		{
//			delete warriorGroups[i][j];
//		}
//
//		delete[] warriorGroups[i];
//	}
//
//}




/*



TANQUE IDLE RIGHT:

     _   |
   _|_| _|_
  (_) |__|
    |_|
    | |

TANQUE ATTACK RIGHT:

	 _     /
   _|_|  _/_
  (_) |__/
	|_|
	| |

TANQUE IDLE LEFT:

    |   _   
   _|_ |_|_ 
    |__| (_)
       |_|
       | |




TANQUE ATTACK LEFT:

  \     _
  _\_  |_|_
    \__| (_)
 	   |_|
       | |
	

ARQUERO IDLE RIGHT:

    _
   |_| |\
   | |-||
   |_| |/
   | |

ARQUERO ATTACK RIGHT:

    _
   |_| |\
   | |-||  --->
   |_| |/
   / |

ARQUERO IDLE LEFT:
     
          _
      /| |_|
      ||-| |
      \| |_| 
         | |
	  
ARQUERO ATTACK LEFT:

          _
      /| |_|
 <--- ||-| |
      \| |_|
         | |
	  
HECHICERO IDLE RIGHT:

    _    _ 
   |_|  |
  /| |\ |
  ||_| \|
   | |  |

HECHICERO ATTACK RIGHT
           _
    _     /    
   |_|   /    <*)
  /| |\_/    
  ||_| /
   | |  

HECHICERO IDLE LEFT:

         _    _    
          |  |_|  
          | /| |\ 
          |/ |_||
          |  | |  

HECHICERO ATTACK LEFT:
       _
        \     _
  (*>    \   |_|
          \_/| |\
           \ |_||
             | |
           
DEAD RIGHT:
   
  _________
  __|___|__|

DEAD LEFT:

		   _________
		  |__|___|__



*/