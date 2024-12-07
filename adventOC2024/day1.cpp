#include "day1.h"

#include <iostream>
#include <map>
#include <sstream>
#include <fstream>
#include <vector>
#include <algorithm>	



int calculateDistance(std::string input_file)
{
	std::ifstream the_file(input_file);

	std::vector<int> list1;
	std::vector<int> list2;


	if (!the_file.is_open())
	{
		std::cout << "Failed to open input file" << std::endl;
		return -1;
	}

	std::string temp;
	while (the_file >> temp)
	{
		list1.emplace_back(std::stoi(temp));
		the_file >> temp;
		list2.emplace_back(std::stoi(temp));
	}

	std::sort(list1.begin(), list1.end());
	std::sort(list2.begin(), list2.end());

	int distance = 0;

	for (int i = 0; i < list1.size(); i++)
	{
		distance += abs(list1[i] - list2[i]);
	}

	bool breakpoint = false;

	return distance;
}

int calculateSimilarity(std::string input_file)
{
	std::ifstream the_file(input_file);

	std::vector<int> list1;
	std::vector<int> list2;


	if (!the_file.is_open())
	{
		std::cout << "Failed to open input file" << std::endl;
		return -1;
	}

	std::string temp;
	while (the_file >> temp)
	{
		list1.emplace_back(std::stoi(temp));
		the_file >> temp;
		list2.emplace_back(std::stoi(temp));
	}

	std::map<int, int> list2Occurrences;

	for (int i = 0; i < list2.size(); i++)
	{
		list2Occurrences[list2[i]]++;
	}

	int similarity = 0;

	for (int i = 0; i < list1.size(); i++)
	{
		if (list2Occurrences[list1[i]])
		{
			similarity += list2Occurrences[list1[i]] * list1[i];
		
		}
	}

	return similarity;
}
