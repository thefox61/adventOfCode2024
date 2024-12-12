#include "day3.h"
#include <regex>
#include <iostream>

int calculateValue(std::string input_file)
{
	int result = 0;

	//std::string test_input("xmul(2,4)%&mul[3,7]!@^do_not_mul(5,5)+mul(32,64]then(mul(11,8)mul(8,5))s");

	std::stringstream input;

	std::ifstream the_file(input_file);

	input << the_file.rdbuf();

	std::string input_string = input.str();

	std::regex mul_regex("[m][u][l][(][0-9]*[,][0-9]*[)]");
	std::regex do_regex("[d][o][(][)]");
	std::regex dont_regex("[d][o][n]['][t][(][)]");

	std::smatch mul_match;
	std::smatch do_match;
	std::smatch dont_match;

	
	

	bool do_mul = true;

	while (std::regex_search(input_string, mul_match, mul_regex))
	{

		std::regex_search(input_string, do_match, do_regex);
		std::regex_search(input_string, dont_match, dont_regex);

		if (do_match.position(0) < mul_match.position(0) && (dont_match.position(0) > mul_match.position(0) || dont_match.position(0) < do_match.position(0)))
		{
			do_mul = true;
		}
		else if (dont_match.position(0) < mul_match.position(0) && (do_match.position(0) > mul_match.position(0) || do_match.position(0) < dont_match.position(0)))
		{
			do_mul = false;
		}

		if (do_mul)
		{
			std::string instruction = mul_match.str(0);

			int open_bracket = instruction.find_first_of("(");
			int close_bracket = instruction.find_first_of(")");
			int seperator = instruction.find_first_of(",");

			int operator1 = std::stoi(instruction.substr(open_bracket + 1, seperator - 1));
			int operator2 = std::stoi(instruction.substr(seperator + 1, close_bracket - 1));

			result += operator1 * operator2;
		}
	
		input_string = mul_match.suffix().str();
	}

	return result;
}
