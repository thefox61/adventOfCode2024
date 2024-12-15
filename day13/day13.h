#pragma once

// save time includes
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <unordered_map>

enum button
{
	BUTTON_A,
	BUTTON_B
};

struct machine
{
	std::pair<double, double> a_button;

	std::pair<double,double> b_button;

	std::pair<double, double> prize;


	int a_cost = 3;

	int b_cost = 1;

};


std::vector<machine> loadMachines(std::string input_file);


unsigned long long calculateCosts(std::vector<machine>& machines);



long calcCostMat(machine& the_machine);

unsigned long long calcCostSystemOfEquations(machine& the_machine);