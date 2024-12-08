#pragma once

// save time includes
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <unordered_map>

enum operators
{
	add,
	multiply,
	concatenate
};

std::vector< std::pair<unsigned long long, std::vector<int>>> loadEquations(std::string input_file);

unsigned long long calibrationSum(std::vector< std::pair<unsigned long long, std::vector<int>>>& equations);

unsigned long long calibrationSumTwo(std::vector< std::pair<unsigned long long, std::vector<int>>>& equations);


unsigned long long determineOperators(unsigned long long result, std::vector<int>& equation);

unsigned int power(unsigned int base, unsigned int exponent);


bool hasValidOperators(unsigned long long result, std::vector<int>& equation);

bool testValidOperator(unsigned long long result, std::vector<int>& equation, int index, unsigned long long value, operators op);
