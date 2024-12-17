#pragma once
// save time includes
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <unordered_map>

struct robotSimulation
{
	std::vector<std::vector<char>> map;
	
	std::vector<char> moves;

	std::pair<int, int> robot_position;
};

robotSimulation loadSimulation(std::string input_file);

robotSimulation loadWideSimulation(std::string input_file);

void simulate(robotSimulation& simulation, bool wide = false);

void simulateMove(robotSimulation& simulation, char move, bool wide = false);

void moveUp(robotSimulation& simulation);

void moveDown(robotSimulation& simulation);

void moveLeft(robotSimulation& simulation);

void moveRight(robotSimulation& simulation);

void printWarehouse(robotSimulation& simulation);


long calculateGPSCoordinates(robotSimulation& simulation);

long calculateGPSCoordinatesWide(robotSimulation& simulation);


void wideMoveUp(robotSimulation& simulation);

void wideMoveDown(robotSimulation& simulation);


