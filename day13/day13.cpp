#include "day13.h"

#include <glm/matrix.hpp>
#include <glm/vec2.hpp>

#include <cmath>


std::vector<machine> loadMachines(std::string input_file)
{
	std::ifstream the_file(input_file);

	std::string temp;

	std::vector<machine> machines;

	while (std::getline(the_file, temp))
	{	
		machine curr_machine;
		// button a
		int x_start = temp.find_first_of("+") + 1;
		int x_end = temp.find_first_of(",");
		int y_start = temp.find_last_of("+") + 1;

		curr_machine.a_button.first = std::stoi(temp.substr(x_start, x_end - x_start));

		curr_machine.a_button.second = std::stoi(temp.substr(y_start, temp.length() - y_start));

		// button b
		std::getline(the_file, temp);

		x_start = temp.find_first_of("+") + 1;
		x_end = temp.find_first_of(",");
		y_start = temp.find_last_of("+") + 1;

		curr_machine.b_button.first = std::stoi(temp.substr(x_start, x_end - x_start));

		curr_machine.b_button.second = std::stoi(temp.substr(y_start, temp.length() - y_start));

		// prize
		std::getline(the_file, temp);
		x_start = temp.find_first_of("=") + 1;
		x_end = temp.find_first_of(",");
		y_start = temp.find_last_of("=") + 1;

		curr_machine.prize.first = std::stoi(temp.substr(x_start, x_end - x_start));

		curr_machine.prize.second = std::stoi(temp.substr(y_start, temp.length() - y_start));

		curr_machine.prize.first += 10000000000000;
		curr_machine.prize.second += 10000000000000;

		// empty line
		std::getline(the_file, temp);

		machines.emplace_back(curr_machine);
	}
	return machines;
}


unsigned long long calculateCosts(std::vector<machine>& machines)
{
	unsigned long long cost = 0;

	for (int i = 0; i < machines.size(); i++)
	{
		unsigned long long curr_machine_cost = calcCostSystemOfEquations(machines[i]);

		cost += curr_machine_cost;
	}

	return cost;
}

long calcCostMat(machine& the_machine)
{
	glm::mat2 buttons(the_machine.a_button.first, the_machine.a_button.second, the_machine.b_button.first, the_machine.b_button.second);

	glm::uvec2 prize_location(the_machine.prize.first, the_machine.prize.second);

	glm::mat2 buttons_inverse = glm::inverse(buttons);

	

	long double optimal_presses_a = buttons_inverse[0][0] * the_machine.prize.first + buttons_inverse[0][1] * the_machine.prize.second;

	long double optimal_presses_b = buttons_inverse[1][0] * the_machine.prize.first + buttons_inverse[1][1] * the_machine.prize.second;
	
	
	std::vector<long double> optimal_presses{optimal_presses_a, optimal_presses_b};


	std::vector<long long> optimal_presses_vec;


	for (int i = 0; i < 2; i++)
	{
		long long rounded = std::round(optimal_presses[i]);

		if (std::abs((long double)rounded - optimal_presses[i]) > 0.05)
		{
			return 0;
		}

		optimal_presses_vec.emplace_back(rounded);
	}

	long cost = the_machine.a_cost * optimal_presses_vec[0] + the_machine.b_cost * optimal_presses_vec[1];

	return cost;
}

unsigned long long calcCostSystemOfEquations(machine& the_machine)
{
	// system of equations
	// button_A_x + button_B_x = prize_x
	// button_A_y + button_B_y = prize_y

	// D
	// button_A_x button_A_y
	// button_B_x button_B_y
	double D = (the_machine.a_button.first * the_machine.b_button.second) - (the_machine.b_button.first * the_machine.a_button.second);

	// Dx
	// prize_x button_B_x
	// prize_y button_B_y
	double Dx = (the_machine.prize.first * the_machine.b_button.second) - (the_machine.prize.second * the_machine.b_button.first);

	// Dy
	// button_A_x prize_x
	// button_A_y prize_y
	double Dy = (the_machine.a_button.first * the_machine.prize.second) - (the_machine.a_button.second * the_machine.prize.first);


	double optimal_presses_a = Dx / D;

	double optimal_presses_b = Dy / D;

	std::vector<double> optimal_presses{ optimal_presses_a, optimal_presses_b };


	std::vector<long long> optimal_presses_vec;


	for (int i = 0; i < 2; i++)
	{
		if ((unsigned long long)optimal_presses[i] != optimal_presses[i])
		{
			return 0;
		}

		//optimal_presses_vec.emplace_back(rounded);
	}

	unsigned long long cost = the_machine.a_cost * optimal_presses[0] + the_machine.b_cost * optimal_presses[1];


	return cost;
}
