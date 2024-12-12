#include "day11.h"
#include <iostream>

int main()
{
	std::vector<long long> stones = loadStones("day11input.txt");

	long long result_25 = blinks(stones, 25);
	long long result_75 = blinks(stones, 75);


	std::cout << "Advent of Code Day 11" << std::endl;

	std::cout << "25 Blinks Result: " << result_25 << std::endl;

	std::cout << "75 Blinks Result: " << result_75 << std::endl;


	return 0;
}