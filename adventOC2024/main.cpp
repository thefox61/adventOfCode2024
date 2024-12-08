
#include "day1.h"
#include "day2.h"
#include "day3.h"
#include "day4.h"
#include "day5.h"
#include "day6.h"
#include "day7.h"
#include "day8.h"

#include <iostream>


int main()
{
	
	std::vector<std::vector<char>> map = loadMap("day8input.txt");
	

	int result = countAntinodesTwo(map);

	std::cout << result << std::endl;


	return 0;
}