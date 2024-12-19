#include "day17.h"
#include <iostream>

int main()
{
	program the_program = loadProgram("day17input.txt");

	// std::string output = executeProgram(the_program);

	long long a_value = findAValue(the_program);

	std::cout << "Advent of Code Day 17" << std::endl;

	// std::cout << output << std::endl;

	std::cout << a_value << std::endl;

	return 0;
}