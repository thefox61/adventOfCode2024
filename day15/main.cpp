#include "day15.h"
#include <iostream>

int main()
{

	robotSimulation simulation = loadSimulation("inputDay15.txt");

	//simulate(simulation);

	printWarehouse(simulation);

	long coordinate_sum = calculateGPSCoordinates(simulation);

	// part 2

	robotSimulation wide_simulation = loadWideSimulation("inputDay15.txt");


	simulate(wide_simulation, true);

	long coordinate_sum_wide = calculateGPSCoordinatesWide(wide_simulation);

	printWarehouse(wide_simulation);
	
	std::cout << "Advent of Code Day 15" << std::endl;

	std::cout << coordinate_sum << std::endl;

	std::cout << coordinate_sum_wide << std::endl;

	return 0;
}