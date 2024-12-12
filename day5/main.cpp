#include "day5.h"
#include <iostream>

int main()
{
	std::unordered_map<int, std::vector<int>> rules;
	std::vector <std::vector<int>> manuals;

	loadManualsAndRules("day5input.txt", rules, manuals);

	int middle_values_valid = countMiddleValues(rules, manuals);

	int middle_values_invalid = countMiddleValuesInvalid(rules, manuals);

	std::cout << "Advent of Code Day 5" << std::endl;

	std::cout << "Valid report middle values: " << middle_values_valid << std::endl;

	std::cout << "Invalid report middle values: " << middle_values_invalid << std::endl;

	return 0;
}