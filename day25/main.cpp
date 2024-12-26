#include <iostream>
#include "day25.h"

int main()
{

	locksAndKeys locks_and_keys = loadSchematics("day25input.txt");

	long long possible_fits = countPossiblePairs(locks_and_keys);

	std::cout << "Advent of Code Day 25" << std::endl;

	std::cout << possible_fits << std::endl;

	return 0;
}