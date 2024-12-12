#pragma once

// save time includes
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <unordered_map>

std::vector<std::vector<char>> loadPuzzle(std::string input_file);

int countWords(std::vector<std::vector<char>>& puzzle);


char getIndex(int i, int j, std::vector<std::vector<char>>& puzzle);


int checkXmas(int i, int j, std::vector<std::vector<char>>& puzzle);

bool checkMasX(int i, int j, std::vector<std::vector<char>>& puzzle);

int countX(std::vector<std::vector<char>>& puzzle);


