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


unsigned long long getNextSecretNum(unsigned long long secret_num);

unsigned long long calcNthSecretNum(unsigned long long secret_num, int n);

unsigned long long getSecretNumSum(std::string input_file);

std::vector<int> findBestSequence(std::string input_file, long long& most_bananas);


void getSequences(unsigned long long secret_num, int n, std::map<std::vector<int>, int >& sequences);

