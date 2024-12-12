#include "day8.h"
#include <iostream>

int main()
{

	std::vector<std::vector<char>> map = loadMap("day8input.txt");

	int antinode_count1 = countAntinodes(map);

	int antinode_count2 = countAntinodesTwo(map);


	std::cout << "Advent of Code Day 8" << std::endl;

	std::cout << "Antinode count v1: " << antinode_count1 << std::endl;

	std::cout << "Antinode count v2: " << antinode_count2 << std::endl;

	return 0;
}