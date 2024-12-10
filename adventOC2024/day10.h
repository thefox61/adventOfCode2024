#pragma once

// save time includes
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <unordered_map>


std::vector<std::vector<int>> loadTopoMap(std::string input_file);

int getIndexValue(int i, int j, std::vector<std::vector<int>>& topo_map);

int countTrails(std::vector<std::vector<int>>& topo_map);

int countTrail(int i, int j, std::vector<std::vector<int>>& topo_map, std::vector<std::pair<int, int>>* visited_nines);


