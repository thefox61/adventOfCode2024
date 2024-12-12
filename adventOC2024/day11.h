#pragma once

// save time includes
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <unordered_map>


struct blinkThreadParameters
{
	int num_blinks;
	std::vector<long long> stones;
	bool threadDone = false;
};

std::vector<long long> loadStones(std::string input_file);

void blink(std::vector<long long>& stones);

void blink(std::unordered_map<long long, long long>& stones, std::unordered_map<long long, std::vector<long long>>& next_values);


long long blinks(std::vector<long long>& stones, int num_blinks);

long long blinks2(std::vector <long long>& stones, int num_blinks);

blinkThreadParameters* spawnBlinkThread(std::vector<long long>& stones, int num_blinks);