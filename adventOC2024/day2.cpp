#include "day2.h"
#include <sstream>
#include <fstream>

#include <string>


int getNumSafe(std::string input_file)
{
	// std::vector<std::vector<int>> reports;

	int num_safe = 0;

	std::ifstream the_file(input_file);

	std::string temp;

	while (std::getline(the_file, temp))
	{
		std::vector<int> new_report;
		

		std::stringstream report_stream(temp);

		std::string input;
		while (report_stream >> input)
		{
			new_report.emplace_back(std::stoi(input));
		}

		if (checkSafe(new_report))
		{
			num_safe++;
		}
	}

	bool breakpoint = false;

	return num_safe;
}

bool checkSafe(std::vector<int>& report)
{
	// determine if decreasing or increasing
	// for each element, check if maintaining order, and check distance 
	if (report.size() <= 1)
	{
		return true;
	}

	return checkAscending(report) || checkDescending(report);

	if (report[0] < report[1])
	{
		return checkAscending(report);
	}
	if (report[0] > report[1])
	{
		return checkDescending(report);
	}

	if (report[0] == report[1])
	{
		if (checkAscending(report) || checkDescending(report))
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	return true;
}

// both modified to allow for problem dampening
bool checkAscending(std::vector<int>& report, bool removed)
{
	int problem_level = 0;
	for (int i = 1; i < report.size(); i++)
	{
		if (!(report[i - 1] < report[i]))
		{
			if (removed)
			{
				return false;
			}
			std::vector<int> report_removed1(report);
			std::vector<int> report_removed2(report);

			report_removed1.erase(report_removed1.begin() + i);
			report_removed2.erase(report_removed2.begin() + i - 1);

			return checkAscending(report_removed1, true) || checkAscending(report_removed2, true);
			
		}

		int difference = abs(report[i - 1] - report[i]);

		if (difference < 1 || difference > 3)
		{
			if (removed)
			{
				return false;
			}

			std::vector<int> report_removed1(report);
			std::vector<int> report_removed2(report);

			report_removed1.erase(report_removed1.begin() + i);
			report_removed2.erase(report_removed2.begin() + i - 1);

			return checkAscending(report_removed1, true) || checkAscending(report_removed2, true);
		}
	}
	return true;
}

bool checkDescending(std::vector<int>& report, bool removed)
{
	int problem_level = 0;

	for (int i = 1; i < report.size(); i++)
	{
		if (!(report[i - 1] > report[i]))
		{

			if (removed)
			{
				return false;
			}
			std::vector<int> report_removed1(report);
			std::vector<int> report_removed2(report);

			report_removed1.erase(report_removed1.begin() + i);
			report_removed2.erase(report_removed2.begin() + i - 1);

			return checkDescending(report_removed1, true) || checkDescending(report_removed2, true);
		}

		int difference = abs(report[i - 1] - report[i]);

		if (difference < 1 || difference > 3)
		{

			if (removed)
			{
				return false;
			}
			std::vector<int> report_removed1(report);
			std::vector<int> report_removed2(report);

			report_removed1.erase(report_removed1.begin() + i);
			report_removed2.erase(report_removed2.begin() + i - 1);

			return checkDescending(report_removed1, true) || checkDescending(report_removed2, true);
		}
	}
	return true;
}


