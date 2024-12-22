#include "day20.h"
#include <iostream>

int main()
{
	graph the_graph = loadGraph("day20input.txt");

	std::vector<int> final_path;

	long long path_cost = findShortestPathLength(the_graph, final_path);

	//long long num_cheats = checkAllCheats(the_graph, final_path, 101);

	long long num_cheats2 = checkAllCheatsPart2(the_graph, final_path, 100);

	std::cout << "Advent of Code Day 20" << std::endl;

	//std::cout << num_cheats << std::endl;

	std::cout << num_cheats2 << std::endl;

	return 0;
}

