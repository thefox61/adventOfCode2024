#include <iostream>
#include "day24.h"


int main()
{

	elvenDevice elven_device = loadDevice("day24input.txt");


	std::set<std::string> swapped_wires = identifySwappedWires(elven_device);
	 

	unsigned long long result = evaluateDevice(elven_device);

	std::cout << "Advent of code Day 24" << std::endl;

	std::cout << result << std::endl;

	for (std::string wire : swapped_wires)
	{
		if (!wire.empty())
		{
			std::cout << wire << ',';
		}
	}
	std::cout << std::endl;

	return 0;
} 