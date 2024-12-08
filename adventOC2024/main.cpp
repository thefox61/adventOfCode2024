
#include "day1.h"
#include "day2.h"
#include "day3.h"
#include "day4.h"
#include "day5.h"
#include "day6.h"
#include "day7.h"

#include <iostream>


int main()
{
	
	std::vector<std::pair<unsigned long long, std::vector<int>>> equations = loadEquations("day7input.txt");

	unsigned long long result = calibrationSumTwo(equations);
	
	std::cout << result << std::endl;

	

	bool breakpoint = false;

	return 0;
}