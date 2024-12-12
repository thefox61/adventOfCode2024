#include "day7.h"
#include <iostream>

int main()
{
	std::vector< std::pair<unsigned long long, std::vector<int>>> equations = loadEquations("day7input.txt");

	long long calibration_sum1 = calibrationSum(equations);

	long long calibration_sum2 = calibrationSumTwo(equations);



	std::cout << "Advent of Code Day 7" << std::endl;

	std::cout << "Calibration sum 1: " << calibration_sum1 << std::endl;

	std::cout << "Calibration sum 2: " << calibration_sum2 << std::endl;

	return 0;

}