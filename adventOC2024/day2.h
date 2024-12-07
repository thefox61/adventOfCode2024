#pragma once
#include <string>
#include <vector>


int getNumSafe(std::string input_file);


bool checkSafe(std::vector<int>& report);

bool checkAscending(std::vector<int>& report, bool removed = false);

bool checkDescending(std::vector<int>& report, bool removed = false);
