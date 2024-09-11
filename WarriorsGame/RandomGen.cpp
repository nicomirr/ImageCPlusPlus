#include <iostream>
#include "RandomGen.h"

RandomGen::RandomGen(){}

int RandomGen::RandomRange(int minInclusive, int maxInclusive)
{
	return minInclusive + (rand() % (maxInclusive - minInclusive + 1));
}