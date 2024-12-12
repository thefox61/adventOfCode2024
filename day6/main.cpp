#include "day6.h"
#include <iostream>

int main()
{
	node* root_node_part1;
	std::vector<std::vector<node>> graph_part1;

	node* root_node_part2;
	std::vector<std::vector<node>> graph_part2;

	loadGraph("day6input.txt", root_node_part1, graph_part1);

	int distinct_positions = countDistinctPath(root_node_part1, graph_part1);

	loadGraph("day6input.txt", root_node_part2, graph_part2);

	int obstacle_locations = countObstacleLocations(root_node_part2, graph_part2);


	std::cout << "Advent of Code Day 6" << std::endl;

	std::cout << "Distinct guard positions: " << distinct_positions << std::endl;

	std::cout << "Possible obstacle locations: " << obstacle_locations << std::endl;

	return 0;
}