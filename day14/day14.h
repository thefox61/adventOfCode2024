#pragma once

// save time includes
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <unordered_map>

struct robot
{
	std::pair<int, int> start_pos;
	std::pair<int, int> curr_pos;

	std::pair<int, int> velocity;

	int second_count = 0;
};


std::vector<robot> loadRobots(std::string input_file);

long long calculateSafetyFactor(std::vector<robot>& robots, int x_size, int y_size);

int determineQuadrant(robot& robot, int x_size, int y_size);

void updateRobotPosition(robot& the_robot, int seconds, int x_size, int y_size);

void updateAllRobots(std::vector<robot>& robots, int seconds, int x_size, int y_size);

void printRobotPositions(std::vector<robot>& robots, int x_size, int y_size);


bool hasOverlap(std::vector<robot>& robots, int x_size, int y_size);

int findTreeSeconds(std::vector<robot>& robots, int x_size, int y_size);

