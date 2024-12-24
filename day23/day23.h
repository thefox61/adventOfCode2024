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


struct computer
{
	unsigned long id;

	std::string name;

	std::set<std::string> connections;

	computer(unsigned long id_, std::string name_) : id(id_), name(name_) 
	{
		connections = std::set<std::string>();
	};
};

struct computerGraph
{
	std::vector<computer> computers;

	std::map<std::string, computer*> computer_map;


};


computerGraph loadComputerGraph(std::string input_file);


long long findConnectedSetsT(computerGraph& computer_graph);

std::vector<std::string> findLargestConnectedSet(computerGraph& computer_graph);

