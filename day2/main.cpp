#include "day2.h"
#include <iostream>

int main()
{
	int result = getNumSafe("day2input.txt");

	std::cout << "Advent of Code Day 2" << std::endl;

	std::cout << "Number of safe reports: " << result << std::endl;

	return 0;
}