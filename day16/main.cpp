#include "day16.h"
#include <iostream>


int main()
{
	reindeer the_reindeer;
	std::vector<std::vector<node>> graph = loadGraph("day16input.txt", the_reindeer);

	the_reindeer.curr_direction = direction::EAST;

	long cost = calculateShortestPath(graph, the_reindeer);

	long nodes_in_paths = calculateNodesShortestPaths(graph, the_reindeer);

	std::cout << "Advent of Code Day 16" << std::endl;
	std::cout << cost << std::endl;
	std::cout << nodes_in_paths << std::endl;


	return 0;
}