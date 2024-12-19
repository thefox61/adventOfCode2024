#include "day18.h"
#include <iostream>

int main()
{
	std::string input_file = "day18input.txt";
	int num_bytes_to_load = 1024;

	graph the_graph = loadGraph(input_file, num_bytes_to_load, 71);

	std::vector<std::pair<int, int>> bytes = loadBytes(input_file);

	long path_length = findShortestPathLength(the_graph);

	std::pair<int, int> blocking_byte = findFirstBlockingByte(the_graph, bytes, num_bytes_to_load);
	
	std::cout << "Advent of Code Day 18" << std::endl;

	std::cout << path_length << std::endl;

	std::cout << "Blocking byte: " << blocking_byte.second << "," << blocking_byte.first << std::endl;

	return 0;
}