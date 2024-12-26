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
#include <queue>


struct heights
{
	int height_0 = 0;
	int height_1 = 0;
	int height_2 = 0;
	int height_3 = 0;
	int height_4 = 0;

	bool lock = true;
};

struct locksAndKeys
{
	std::vector<heights> locks;
	std::vector<heights> keys;

};


locksAndKeys loadSchematics(std::string input_file);

heights calculateLockHeights(std::vector<std::string> &schematic);

heights calculateKeyHeights(std::vector<std::string>& schematic);


bool checkFit(heights& lock, heights& key);


long long countPossiblePairs(locksAndKeys& locks_and_keys);
