#include "day9.h"
#include <iostream>

int main()
{
	std::vector<int> file_system_vec = loadFileSystem("day9input.txt");

	long long checksum1 = computeChecksum(file_system_vec);


	fileSystem file_system = loadFileSystemBlocks("day9input.txt");

	compactFileSystem(file_system);

	long long checksum2 = computeChecksum(file_system);


	std::cout << "Advent of Code Day 9" << std::endl;

	std::cout << "Checksum 1: " << checksum1 << std::endl;

	std::cout << "Checksum 2: " << checksum2 << std::endl;

	return 0;
}