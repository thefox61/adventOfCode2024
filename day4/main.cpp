#include "day4.h"
#include <iostream>

int main()
{
	std::vector<std::vector<char>> puzzle = loadPuzzle("day4Input.txt");

	int xmas_words_count = countWords(puzzle);
	int x_count = countX(puzzle);

	std::cout << "Advent of Code Day 4" << std::endl;
	std::cout << "XMAS words: " << xmas_words_count << std::endl;
	std::cout << "X XMAS count: " << x_count << std::endl;

	return 0;
}
