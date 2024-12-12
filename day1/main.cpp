#include "day1.h"
#include <iostream>
int main()
{
	int part1Result = calculateDistance("day1Input.txt");

	int part2Result = calculateSimilarity("day1Input.txt");


	std::cout << "Advent of Code Day 1!" << std::endl;

	std::cout << "Part 1 Answer: " << part1Result << std::endl;

	std::cout << "Part 2 Answer: " << part2Result << std::endl;

	return 0;
}