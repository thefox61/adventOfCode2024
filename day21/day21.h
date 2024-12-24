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

struct pathState
{
	int i;
	int j;

	std::string inputs;

	pathState(int i_, int j_, std::string inputs_) : i(i_), j(j_), inputs(inputs_) {};
};

struct savedCost
{
	int i0;
	int j0;

	int i1;
	int j1;

	int robot_num;

	savedCost(int i0_, int j0_, int i1_, int j1_, int robot_num_) : i0(i0_), j0(j0_) , i1(i1_) , j1(j1_), robot_num(robot_num_) {};

	bool operator<(const savedCost& other)  const
	{
		return robot_num < other.robot_num || robot_num == other.robot_num && i0 < other.i0 && i1 < other.i1 && j0 < other.j0 && j1 < other.j1;
	}

	bool operator==(const savedCost& other)  const
	{
		return (robot_num == other.robot_num && i0 == other.i0 && j0 == other.j0 && i1 == other.i1 && j1 == other.j1);
	}
};


void loadPositionMaps();

unsigned long long hashCost(int i0, int j0, int i1, int j1, int robot_num);


unsigned long long calculateLowestCost(int i0, int j0, int i1, int j2);

unsigned long long calculateRobotCost(std::string input, int robot_num);

unsigned long long calculateLowestDirectionPad(int i0, int j0, int i1, int j1, int robot_num);

unsigned long long calculateComplexity(std::string code);

unsigned long long calculateComplexetiesSum(std::string input_file);


