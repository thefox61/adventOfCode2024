#include "day4.h"

std::vector<std::vector<char>> loadPuzzle(std::string input_file)
{
	std::ifstream the_file(input_file);
	std::string temp;

	std::vector<std::vector<char>> puzzle;

	while (std::getline(the_file, temp))
	{
		std::vector<char> new_row;
		for (int i = 0; i < temp.length(); i++)
		{
			new_row.emplace_back(temp[i]);
		}
		puzzle.emplace_back(new_row);
	}

	return puzzle;
}

int countWords(std::vector<std::vector<char>>& puzzle)
{
	int count = 0;

	for (int i = 0; i < puzzle.size(); i++)
	{
		for (int j = 0; j < puzzle[i].size(); j++)
		{
			count += checkXmas(i, j, puzzle);
		}
	}
	return count;
}

char getIndex(int i, int j, std::vector<std::vector<char>>& puzzle)
{
	if (i >= puzzle.size() || j >= puzzle[i].size())
	{
		return 'F';
	}
	return puzzle[i][j];
}

int checkXmas(int i, int j, std::vector<std::vector<char>>& puzzle)
{
	int result = 0;
	if (puzzle[i][j] != 'X')
	{
		return result;
	}

	// check forward

	if (getIndex(i, j, puzzle) == 'X' && getIndex(i, j + 1, puzzle) == 'M' && getIndex(i, j + 2, puzzle) == 'A' && getIndex(i, j + 3, puzzle) == 'S')
	{
		result++;
	}

	// check backward
	if (getIndex(i, j, puzzle) == 'X' && getIndex(i, j - 1, puzzle) == 'M' && getIndex(i, j - 2, puzzle) == 'A' && getIndex(i, j - 3, puzzle) == 'S')
	{
		result++;
	}

	// check up
	if (getIndex(i, j, puzzle) == 'X' && getIndex(i + 1, j, puzzle) == 'M' && getIndex(i + 2, j, puzzle) == 'A' && getIndex(i + 3, j, puzzle) == 'S')
	{
		result++;
	}

	// check down
	if (getIndex(i, j, puzzle) == 'X' && getIndex(i - 1, j, puzzle) == 'M' && getIndex(i - 2, j, puzzle) == 'A' && getIndex(i - 3, j, puzzle) == 'S')
	{
		result++;
	}

	// diagonals
	
	// up back
	if (getIndex(i, j, puzzle) == 'X' && getIndex(i - 1, j - 1, puzzle) == 'M' && getIndex(i - 2, j - 2, puzzle) == 'A' && getIndex(i - 3, j - 3, puzzle) == 'S')
	{
		result++;
	}

	// up forward
	if (getIndex(i, j, puzzle) == 'X' && getIndex(i - 1, j + 1, puzzle) == 'M' && getIndex(i - 2, j + 2, puzzle) == 'A' && getIndex(i - 3, j + 3, puzzle) == 'S')
	{
		result++;
	}

	// down back
	if (getIndex(i, j, puzzle) == 'X' && getIndex(i + 1, j - 1, puzzle) == 'M' && getIndex(i + 2, j - 2, puzzle) == 'A' && getIndex(i + 3, j - 3, puzzle) == 'S')
	{
		result++;
	}

	// down forward
	if (getIndex(i, j, puzzle) == 'X' && getIndex(i + 1, j + 1, puzzle) == 'M' && getIndex(i + 2, j + 2, puzzle) == 'A' && getIndex(i + 3, j + 3, puzzle) == 'S')
	{
		result++;
	}




	return result;
}

bool checkMasX(int i, int j, std::vector<std::vector<char>>& puzzle)
{
	if (getIndex(i, j, puzzle) != 'A')
	{
		return false;
	}

	if (getIndex(i - 1, j - 1, puzzle) == 'M' && getIndex(i + 1, j + 1, puzzle) == 'S' || getIndex(i - 1, j - 1, puzzle) == 'S' && getIndex(i + 1, j + 1, puzzle) == 'M')
	{
		if (getIndex(i - 1, j + 1, puzzle) == 'M' && getIndex(i + 1, j - 1, puzzle) == 'S' || getIndex(i - 1, j + 1, puzzle) == 'S' && getIndex(i + 1, j - 1, puzzle) == 'M')
		{
			return true;
		}
	}


	return false;
}

int countX(std::vector<std::vector<char>>& puzzle)
{
	int count = 0;

	for (int i = 0; i < puzzle.size(); i++)
	{
		for (int j = 0; j < puzzle[i].size(); j++)
		{
			if (checkMasX(i, j, puzzle))
			{
				count++;
			}

		}
	}
	return count;
}
