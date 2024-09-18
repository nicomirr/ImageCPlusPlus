#include "Game.h"


int Game::drawingsCurrentHeight;

int Game::groupPoints[TOTAL_GROUPS];

Warrior* Game::warriorGroups[TOTAL_GROUPS][WARRIORS_IN_GROUPS];

Game::Game(){ }

Game::~Game(){ }

void Game::InitGame()
{
	drawingsCurrentHeight = 0;
	srand(time(NULL));
}

void Game::Play()
{
	InitGame();
	ResetPointers();
	Gameloop();
}

void Game::Gameloop() 
{
	GenerateRandomWarriors();
	DisplayGroups();

	int firstAttackerGroup = rand() % TOTAL_GROUPS;
	    
	std::cout << "Comienza atacando el grupo " << firstAttackerGroup + 1 << "." << std::endl;
	std::cin.get();
	system("cls");

	AttackState attackState = AttackState::None;	
	int aliveGroups = TOTAL_GROUPS;
	int winnerGroup = 0;
	bool isTie = false;
	int groupsThatHaveAttacked = 0;
	int remainingWarriorsCurrentGroup = 0;
	bool attackerOnLeft = true;	
	int defenderGroup = firstAttackerGroup == (TOTAL_GROUPS - 1) ? 0 : firstAttackerGroup + 1;

	DisplayIdleState(firstAttackerGroup, defenderGroup, attackerOnLeft, attackState);
	
	std::this_thread::sleep_for(std::chrono::seconds(2));
	system("cls");

	bool inBattle = true;

	while (inBattle)
	{
		BattleState(winnerGroup, groupsThatHaveAttacked, firstAttackerGroup, defenderGroup, attackerOnLeft, attackState,
			       inBattle, isTie);
	}

	if (!isTie)
	{
		std::cout << "Ha ganado el grupo " << winnerGroup << "." << std::endl;
	}
	else
	{
		std::cout << "Empate." << std::endl;
	}

	std::cin.get();

	//DeletePointers();	
	
	PlayAgainQuestion();	
		
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

	system("cls");

	delete randomGen;
	randomGen = nullptr;
}
void Game::DisplayGroups()
{
	system("cls");

	for (int group = 0; group < TOTAL_GROUPS; group++)
	{
		Warrior warriorGroup;

		for (int warrior = 0; warrior < WARRIORS_IN_GROUPS; warrior++)
		{
			warriorGroup = warriorGroup + *warriorGroups[group][warrior];
		}

		std::cout << "Grupo " << group + 1 << std::endl;

		warriorGroup.ShowStatistics();

		std::cin.get();

	}
}


void Game::BattleState(int &winnerGroup, int &groupsThatHaveAttacked, int firstAttackerGroup, int defenderGroup, bool &attackerOnLeft,
	AttackState attackState, bool &inBattle, bool &isTie)
{
	winnerGroup = 0;
	groupsThatHaveAttacked = 0;

	for (int currentAttackingGroup = firstAttackerGroup;
		currentAttackingGroup < TOTAL_GROUPS; currentAttackingGroup++)
	{
		defenderGroup = currentAttackingGroup == (TOTAL_GROUPS - 1) ? 0 : currentAttackingGroup + 1;
		drawingsCurrentHeight = 0;

		DisplayAttackState(defenderGroup, currentAttackingGroup, attackerOnLeft, attackState);

		std::this_thread::sleep_for(std::chrono::seconds(2));
		system("cls");

		DisplayIdleState(currentAttackingGroup, defenderGroup, attackerOnLeft, attackState);

		attackerOnLeft = !attackerOnLeft;

		std::this_thread::sleep_for(std::chrono::seconds(2));

		CheckForWinners(winnerGroup, currentAttackingGroup, inBattle);
		if (!inBattle) return;

		CheckForTie(isTie, inBattle);
		if (!inBattle) return;

		groupsThatHaveAttacked++;

		ResetCounterIfNeeded(groupsThatHaveAttacked, currentAttackingGroup);

		//en caso de haberse reiniciado contador, con esto se frena el for cuando se hayan recorrido todos los grupos, y no cuando termine el contador
		if (groupsThatHaveAttacked == TOTAL_GROUPS) return;
	}
}


void Game::DisplayIdleState(int currentAttackerGroup, int defenderGroup, bool attackerOnLeft, AttackState attackState)
{
	drawingsCurrentHeight = 0;

	for (int currentAttackingGroup = currentAttackerGroup; currentAttackingGroup < TOTAL_GROUPS; currentAttackingGroup++)
	{
		defenderGroup = currentAttackerGroup == (TOTAL_GROUPS - 1) ? 0 : currentAttackerGroup + 1;

		for (int currentWarrior = 0; currentWarrior < WARRIORS_IN_GROUPS; currentWarrior++)
		{
			DrawIdleOrDead(currentAttackingGroup, currentWarrior, defenderGroup,  attackerOnLeft, attackState);
			drawingsCurrentHeight += DRAWINGS_SPACING;
		}

		break;
	}
}
void Game::DisplayAttackState(int defenderGroup, int currentAttackingGroup,	bool attackerOnLeft, AttackState attackState)
{
	for (int currentWarrior = 0; currentWarrior < WARRIORS_IN_GROUPS; currentWarrior++)
	{
		if (warriorGroups[currentAttackingGroup][currentWarrior]->GetHealth() > 0)
		{
			if (warriorGroups[defenderGroup][currentWarrior]->GetHealth() > 0)
			{
				bool displayDamageDealth = false;
				DrawAttack(currentAttackingGroup, currentWarrior, defenderGroup, attackerOnLeft, attackState, displayDamageDealth);
			}
			else if (warriorGroups[defenderGroup][currentWarrior]->GetHealth() <= 0)
			{
				DrawIdleOrDead(currentAttackingGroup, currentWarrior, defenderGroup, attackerOnLeft, attackState);
			}

			attackState = warriorGroups[currentAttackingGroup][currentWarrior]->
				Attack(warriorGroups[defenderGroup][currentWarrior]);

			if (warriorGroups[defenderGroup][currentWarrior]->GetDisplayDamagedState())
			{
				bool displayDamageDealth = true;
				DrawAttack(currentAttackingGroup, currentWarrior, defenderGroup, attackerOnLeft, attackState, displayDamageDealth);

				if (warriorGroups[defenderGroup][currentWarrior]->GetHealth() <= 0)
				{
					groupPoints[currentAttackingGroup]++;
					warriorGroups[defenderGroup][currentWarrior]->SetDisplayDamagedState(false);
				}
			}
		}
		else
		{
			DrawIdleOrDead(currentAttackingGroup, currentWarrior, defenderGroup, attackerOnLeft, attackState);
		}

		drawingsCurrentHeight += DRAWINGS_SPACING;
	}
}


void Game::DrawIdleOrDead(int currentAttackingGroup, int currentWarrior, int defenderGroup, bool attackerOnLeft, AttackState attackState)
{
	Draw(warriorGroups[currentAttackingGroup][currentWarrior], warriorGroups[defenderGroup][currentWarrior], attackerOnLeft,
		BattleMoment::IdleMoment, attackState, false);
}
void Game::DrawAttack(int currentAttackingGroup, int currentWarrior, int defenderGroup, bool attackerOnLeft, AttackState attackState,
	bool displayDamageDealth)
{
	Draw(warriorGroups[currentAttackingGroup][currentWarrior], warriorGroups[defenderGroup][currentWarrior], attackerOnLeft,
		BattleMoment::AttackMoment, attackState, displayDamageDealth);
}
void Game::Draw(Warrior* warriorAttacker, Warrior* warriorDefender, bool attackerIsOnLeft, BattleMoment battleMoment, AttackState attackState, 
	bool showDamage)
{

	if (battleMoment == BattleMoment::IdleMoment)
	{
		warriorAttacker->DrawWarriorIdle(attackerIsOnLeft, drawingsCurrentHeight);
		warriorDefender->DrawWarriorIdle(!attackerIsOnLeft, drawingsCurrentHeight);
				
	}
	else if (battleMoment == BattleMoment::AttackMoment)
	{
		warriorAttacker->DrawWarriorAttack(attackerIsOnLeft, drawingsCurrentHeight);

		if (warriorDefender->GetDisplayDamagedState() && showDamage)
		{
			warriorDefender->DrawWarriorDamaged(!attackerIsOnLeft, drawingsCurrentHeight, attackState);
		}
		else
		{
			warriorDefender->DrawWarriorIdle(!attackerIsOnLeft, drawingsCurrentHeight);
		}

	}

}


void Game::CheckForWinners(int &winnerGroup, int currentAttackingGroup, bool &inBattle)
{
	winnerGroup = currentAttackingGroup + 1;
	if (groupPoints[currentAttackingGroup] >= WARRIORS_IN_GROUPS - 1)
	{
		inBattle = false;
		return;

	}
}
void Game::CheckForTie(bool &isTie, bool &inBattle)
{
	int groupsWithHalfMembers = 0;
	int halfMembers = WARRIORS_IN_GROUPS / 2;

	for (int group = 0; group < TOTAL_GROUPS; group++)
	{
		if (groupPoints[group] == halfMembers)
		{
			groupsWithHalfMembers++;
		}
	}

	if (groupsWithHalfMembers == TOTAL_GROUPS)
	{
		isTie = true;
		inBattle = false;
		return;
	}
}


void Game::ResetCounterIfNeeded(int groupsThatHaveAttacked, int &currentAttackingGroup)
{
	//si el contador llegó al máximo y no se recorrieron todos los grupos, se reinicia contador para recorrer grupos restantes.
	if (groupsThatHaveAttacked < TOTAL_GROUPS && currentAttackingGroup == (TOTAL_GROUPS - 1))
	{
		currentAttackingGroup = -1;
	}
}


void Game::PlayAgainQuestion()
{
	system("cls");
	int input = 0;

	std::cout << "Simular nueva batalla?" << std::endl;
	std::cout << "1. Si." << std::endl;
	std::cout << "2. No." << std::endl;
	std::cin >> input;
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

	if (std::cin.fail())
	{
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		input = 0;
	
		PlayAgainQuestion();
	}

	if (input == 1)
	{
		ResetPointers();
		ResetPoints();
		Gameloop();
	}
	else if (input < 1 || input > 2)
	{
		PlayAgainQuestion();
	}
	
}


void Game::ResetPoints()
{
	for (int i = 0; i < TOTAL_GROUPS; i++)
	{
		groupPoints[i] = 0;
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