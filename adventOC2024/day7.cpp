#include "day7.h"

std::vector<std::pair<int, std::vector<int>>> loadEquations(std::string input_file)
{

	std::ifstream the_file(input_file);

	std::string temp;

	std::vector<std::pair<int, std::vector<int>>> equations;

	while (std::getline(the_file, temp))
	{
		int equation_result;
		std::vector<int> new_equation;


		std::stringstream equation_stream(temp);

		std::string input;
		equation_stream >> input;
		equation_result = std::stoi(input.substr(0, input.length() - 1));

		while (equation_stream >> input)
		{
			new_equation.emplace_back(std::stoi(input));
		}

		equations.emplace_back(equation_result, new_equation);

	}
    return equations;
}
