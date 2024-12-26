#pragma once

// save time includes
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <unordered_map>
#include <set>
#include <map>
#include <queue>


struct gate
{
	enum class gateType
	{
		AND,
		OR,
		XOR,
		NOP
	};


	std::string input_1;
	std::string input_2;

	std::string output;

	gateType type = gateType::NOP;
};

struct elvenDevice
{
	std::map<std::string, int> wires;

	std::deque<gate> gates;
};

struct fullAdder
{
	gate xor1;
	gate and1;
	gate xor2;
	gate and2;

	gate or1;

};

elvenDevice loadDevice(std::string input_file);

unsigned long long evaluateDevice(elvenDevice device);

std::vector<gate> determineDependentGates(std::string wire, elvenDevice device);


unsigned long long determineCorrectResult(elvenDevice device);

std::vector<std::string> findIncorrectOutputWires(elvenDevice device);

void countGateTypes(elvenDevice device);

std::set<std::string> identifySwappedWires(elvenDevice device);

bool validAdder(fullAdder the_adder);


std::set<std::string> diagnoseAddingMachine(std::vector<fullAdder>& adders, std::map<std::string, gate>& output_to_gate, std::map<std::string, std::vector<gate>>& input_to_gate);