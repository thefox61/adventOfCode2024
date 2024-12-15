#include "day13.h"
#include <iostream>

int main()
{
	std::vector<machine> machines = loadMachines("day13input.txt");

	unsigned long long costs = calculateCosts(machines);

	std::cout << "Advent of Code Day 13" << std::endl;

	std::cout << costs << std::endl;

	return 0;
}
