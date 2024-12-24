#include "day21.h"
#include <iostream>

int main()
{

	loadPositionMaps();

	unsigned long long complexity_sum = calculateComplexetiesSum("day21input.txt");

	std::cout << "Advent of Code Day 21" << std::endl;

	std::cout << complexity_sum << std::endl; 

	return 0;
}