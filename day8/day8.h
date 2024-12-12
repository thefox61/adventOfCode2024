#pragma once

// save time includes
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <unordered_map>

std::vector<std::vector<char>> loadMap(std::string input_file);

std::unordered_map<char, std::vector<std::pair<int, int>>> getAntennaFrequencies(std::vector<std::vector<char>>& map);

int countAntinodes(std::vector <std::vector<char>>& map);

int countAntinodesTwo(std::vector <std::vector<char>>& map);

char getAntennaMapIndex(int i, int j, std::vector <std::vector<char>>& map);