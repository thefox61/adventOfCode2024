#include "day19.h"
#include <iostream>

int main()
{

	onsenTowels the_towels = loadOnsenTowels("day19input.txt");

	long possible_patterns = countValidPatterns(the_towels);

	long long pattern_options = countPatternOptions(the_towels);

	std::cout << "Advent of Code Day 19" << std::endl;

	std::cout << possible_patterns << std::endl;

	std::cout << pattern_options << std::endl;


	return 0;
}
