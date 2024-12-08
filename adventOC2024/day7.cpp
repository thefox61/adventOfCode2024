#include "day7.h"

std::vector<std::pair<unsigned long long, std::vector<int>>> loadEquations(std::string input_file)
{

	std::ifstream the_file(input_file);

	std::string temp;

	std::vector<std::pair<unsigned long long, std::vector<int>>> equations;

	while (std::getline(the_file, temp))
	{
		unsigned long long equation_result;
		std::vector<int> new_equation;


		std::stringstream equation_stream(temp);

		std::string input;
		equation_stream >> input;
		std::string result_string = input.substr(0, input.length() - 1);

		equation_result = std::stoll(result_string);

		while (equation_stream >> input)
		{
			new_equation.emplace_back(std::stoi(input));
		}

		equations.emplace_back(equation_result, new_equation);

	}
    return equations;
}

unsigned long long calibrationSum(std::vector<std::pair<unsigned long long, std::vector<int>>>& equations)
{
	unsigned long long result = 0;

	for (int i = 0; i < equations.size(); i++)
	{
		result += determineOperators(equations[i].first, equations[i].second);
	}

	return result;
}

unsigned long long calibrationSumTwo(std::vector<std::pair<unsigned long long, std::vector<int>>>& equations)
{
	unsigned long long result = 0;

	for (int i = 0; i < equations.size(); i++)
	{
		if (hasValidOperators(equations[i].first, equations[i].second))
		{
			result += equations[i].first;
		}
	}

	return result;
}

unsigned long long determineOperators(unsigned long long result, std::vector<int>& equation)
{
	unsigned int num_combinations = power(2, equation.size());
	unsigned int current = 0;

	unsigned int num_operators = equation.size() - 1;

	for (int i = 0; i < num_combinations; i++)
	{
		unsigned long long total = equation[0];

		for (int j = 0; j < num_operators; j++)
		{
			unsigned int curr_bit = power(2, j);

			if (curr_bit & i)
			{
				total *= equation[j + 1];
			}
			else
			{
				total += equation[j + 1];
			}
		}

		if (total == result)
		{
			return total;
		}
	}

	return 0;
}

unsigned int power(unsigned int base, unsigned int exponent)
{
	unsigned int result = 1;
	for (int i = 0; i < exponent; i++)
	{
		result *= base;
	}
	return result;
}

bool hasValidOperators(unsigned long long result, std::vector<int>& equation)
{
	return testValidOperator(result, equation, 1, equation[0], operators::add) || testValidOperator(result, equation, 1, equation[0], operators::multiply) || testValidOperator(result, equation,  1, equation[0], operators::concatenate);
}

bool testValidOperator(unsigned long long result, std::vector<int>& equation, int index, unsigned long long value, operators op)
{
	if (index == equation.size())
	{
		return value == result;
	}


	switch (op) 
	{
		case operators::add:
			value += equation[index];
			break;
		case operators::multiply:
			value *= equation[index];
			break;
		case operators::concatenate:
			std::string  value_string = std::to_string(value);
			std::string next_value = std::to_string(equation[index]);

			std::string concatenated_value = value_string + next_value;

			value = std::stoll(concatenated_value);


			break;
	}


	
	return testValidOperator(result, equation, index + 1, value, operators::add) || testValidOperator(result, equation, index + 1, value, operators::multiply) || testValidOperator(result, equation, index + 1, value, operators::concatenate);
}
