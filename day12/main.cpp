#include "day12.h"
#include <iostream>

int main()
{
	node* root_note = NULL;

	std::vector<std::vector<node>> graph;

	loadGraph("day12input.txt", root_note, graph);


	long long bulk_cost = calculateFenceCostBulk(root_note, graph);

	std::cout << "Advent of Code Day 12" << std::endl;

	std::cout << "Bulk cost: " << bulk_cost << std::endl;


	return 0;
}