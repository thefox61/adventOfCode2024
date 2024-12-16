#include "day14.h"
#include <iostream>


int main()
{
	std::vector<robot> robots = loadRobots("day14input.txt");

	int x_size = 101;
	int y_size = 103;


	//updateAllRobots(robots, 100, x_size, y_size);

	//long safety_factor = calculateSafetyFactor(robots, x_size, y_size);

	long seconds = findTreeSeconds(robots, x_size, y_size);

	printRobotPositions(robots, x_size, y_size);

	std::cout << "Advent of Code Day 14" << std::endl;

	std::cout << seconds << std::endl;
	
	return 0;
}