#pragma once

// try and save (a small amount of) time by including common std libs ahead of time
#include <vector>
#include <unordered_map>
#include <string>
#include <algorithm>
#include <fstream>
#include <sstream>

struct state
{
	state(state* nextState, state* beginningState, std::string stateValue)
	{
		next_state = nextState;
		beginning_state = beginningState;
		state_value = stateValue;
	};

	state* next_state;

	state* beginning_state;

	std::string state_value;
};

int calculateValue(std::string input_file);
