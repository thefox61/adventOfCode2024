#pragma once
// save time includes
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <unordered_map>
#include <set>
#include <map>

struct onsenTowels
{
	std::vector<std::string> towel_colours;

	std::vector<std::string> desired_patterns;
};

onsenTowels loadOnsenTowels(std::string input_file);


bool canBuildPattern(std::string desired_pattern, std::set<std::string>& colours_set);

long countValidPatterns(onsenTowels& the_towels);

long long countPatternOptions(onsenTowels& the_towels);

long long possiblePatternOptions(std::string desired_pattern, std::set<std::string>& colours_set, std::map<std::string, long long>& saved_counts);


