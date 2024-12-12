#include "day11.h"

// for threading the aabb calculation
#define NOMINMAX		// otherwise glm::max does not work
#include <Windows.h>	
#define WIN32_LEAN_AND_MEAN	

DWORD WINAPI calculateBlinks(LPVOID lpParameter);

CRITICAL_SECTION threadRunningCriticalSection;



std::vector<long long> loadStones(std::string input_file)
{
	std::ifstream the_file(input_file);

	std::string temp;

	std::vector<long long> stones;

	while (the_file >> temp)
	{
		stones.emplace_back(std::stoll(temp));
	}
	return stones;
}



void blink(std::vector<long long>& stones)
{
	for (int i = 0; i < stones.size(); i++)
	{
		int size = trunc(log10(stones[i])) + 1;

		if (stones[i] == 0)
		{
			stones[i] = 1;
		}
		else if (size % 2 == 0)
		{
			std::string curr_num_s = std::to_string(stones[i]);

			size = size / 2;

			stones[i] = std::stoll(curr_num_s.substr(0, size));

			stones.push_back(std::stoll(curr_num_s.substr(size, size)));
			i++;
		}
		else
		{
			stones[i] *= 2024;
		}
	}
}

void blink(std::unordered_map<long long, long long>& stones, std::unordered_map<long long, std::vector<long long>>& next_values)
{
	std::unordered_map<long long, long long>::iterator it = stones.begin();

	std::unordered_map<long long, long long> stones_updated;

	while (it != stones.end())
	{
		if (next_values[it->first].empty())
		{
			int size = trunc(log10(it->first)) + 1;

			if (it->first == 0)
			{
				next_values[it->first].push_back(1);
			}
			else if (size % 2 == 0)
			{
				std::string curr_num_s = std::to_string(it->first);

				size = size / 2;

				next_values[it->first].push_back(std::stoll(curr_num_s.substr(0, size)));

				next_values[it->first].push_back(std::stoll(curr_num_s.substr(size, size)));
			}
			else
			{
				next_values[it->first].push_back(it->first * 2024);
				// stones[i] *= 2024;
			}
		}

		for (int i = 0; i < next_values[it->first].size(); i++)
		{
			stones_updated[next_values[it->first][i]] += it->second;
		}

		it++;
	}

	stones = stones_updated;
}

long long blinks(std::vector<long long>& stones, int num_blinks)
{
	std::unordered_map<long long, long long> stones_map;
	std::unordered_map<long long, std::vector<long long>> known_values;

	for (int i = 0; i < stones.size(); i++)
	{
		stones_map[stones[i]]++;
	}


	for (int i = 0; i < num_blinks; i++)
	{
		blink(stones_map, known_values);
	}


	std::unordered_map<long long, long long>::iterator stones_it = stones_map.begin();

	long long result = 0;

	while (stones_it != stones_map.end())
	{
		result += stones_it->second;

		stones_it++;
	}


	return result;
}
long long blinks2(std::vector<long long>& stones, int num_blinks)
{
	InitializeCriticalSection(&threadRunningCriticalSection);

	std::vector<blinkThreadParameters*> thread_params;
	for (int i = 0; i < stones.size(); i++)
	{
		std::vector<long long> new_stones(1, stones[i]);

		thread_params.push_back(spawnBlinkThread(new_stones, num_blinks));
	}

	bool done = false;
	while (!done)
	{
		done = true;
		for(int i = 0; i < thread_params.size(); i++)
		{ 
			if (!thread_params[i]->threadDone)
			{
				done = false;
				break;
			}
		}
		Sleep(10);
	}
	long long result = 0;
	for (int i = 0; i < thread_params.size(); i++)
	{
		result += thread_params[i]->stones.size();
	}

	return result;
}
DWORD WINAPI calculateBlinks(LPVOID lpParameter)
{
	blinkThreadParameters* thread_params = static_cast<blinkThreadParameters*>(lpParameter);

	blinks(thread_params->stones, thread_params->num_blinks);

	EnterCriticalSection(&threadRunningCriticalSection);
	thread_params->threadDone = true;
	LeaveCriticalSection(&threadRunningCriticalSection);
	return 0;
}

blinkThreadParameters* spawnBlinkThread(std::vector<long long>& stones, int num_blinks)
{
	blinkThreadParameters* thread_params = new blinkThreadParameters();

	thread_params->num_blinks = num_blinks;
	thread_params->stones = stones;

	DWORD ThreadID;
	HANDLE threadHandle;

	threadHandle = CreateThread(
		NULL,
		0,
		calculateBlinks,
		thread_params,
		0,
		&ThreadID
	);

	return thread_params;
}
