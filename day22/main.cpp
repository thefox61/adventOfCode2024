#include <iostream>
#include "day22.h"

int main()
{
	unsigned long long secret_num_sum = getSecretNumSum("day22input.txt");

	long long most_bananas = 0;

	std::vector<int> sequence = findBestSequence("day22input.txt", most_bananas);

	std::cout << "Advent of Code Day 22" << std::endl;

	std::cout << secret_num_sum << std::endl;


	std::cout << "Best Sequence: ";

	for (int i = 0; i < sequence.size(); i++)
	{
	std::cout << sequence[i] << " ";
	}
	std::cout << std::endl;

	std::cout << "Most bananas: " << most_bananas << std::endl;

	return 0;
}