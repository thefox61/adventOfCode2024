#include "day23.h"
#include <iostream>

int main()
{

	computerGraph computer_graph = loadComputerGraph("day23input.txt");

	long long num_inter_connected = findConnectedSetsT(computer_graph);

	std::vector<std::string> largest_set = findLargestConnectedSet(computer_graph);

	std::cout << "Advent of code Day 23" << std::endl;

	std::cout << num_inter_connected << std::endl;


	for (std::string c : largest_set)
	{
		std::cout << c << ',';
	}

	std::cout << std::endl;

	return 0;
}