#include "day10.h"
#include <iostream>

int main()
{
	std::vector < std::vector<int>> topo_map = loadTopoMap("day10input.txt");

	int result = countTrails(topo_map);

	std::cout << "Advent of Code Day 10" << std::endl;

	std::cout << "Trailhead ratings sum: " << result << std::endl;

	return 0;
}