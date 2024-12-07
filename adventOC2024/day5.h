#pragma once

// save time includes
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <unordered_map>


bool loadManualsAndRules(std::string input_file, std::unordered_map<int, std::vector<int>>& rules, std::vector <std::vector<int>>& manuals);

bool validateManual(std::unordered_map<int, std::vector<int>>& rules, std::vector<int>& manual);

int countValidReports(std::unordered_map<int, std::vector<int>>& rules, std::vector <std::vector<int>>& manuals);

int countMiddleValues(std::unordered_map<int, std::vector<int>>& rules, std::vector <std::vector<int>>& manuals);

int countMiddleValuesInvalid(std::unordered_map<int, std::vector<int>>& rules, std::vector <std::vector<int>>& manuals);

std::vector<std::pair<int, int>> findConflicts(std::unordered_map<int, std::vector<int>>& rules, std::vector<int>& manual);

bool findAndSwapConflict(std::unordered_map<int, std::vector<int>>& rules, std::vector<int>& manual);