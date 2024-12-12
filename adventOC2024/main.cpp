
#include "day1.h"
#include "day2.h"
#include "day3.h"
#include "day4.h"
#include "day5.h"
#include "day6.h"
#include "day7.h"
#include "day8.h"
#include "day9.h"
#include "day10.h"
#include "day11.h"

#include <iostream>


int main()
{
	std::vector<long long> stones = loadStones("day11input.txt");
	

	long long result = blinks2(stones, 75);

	std::cout << result << std::endl;

	bool breakpoint = false;

	return 0;
}