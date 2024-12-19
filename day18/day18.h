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

enum class direction
{
	NORTH,
	EAST,
	WEST,
	SOUTH
};

struct node
{
	unsigned int id;

	node* north = NULL;
	node* east = NULL;
	node* west = NULL;
	node* south = NULL;

	char value;

	node(char value_, unsigned int id_)
	{
		value = value_;

		id = id_;
	}
};

struct graph
{
	std::vector<std::vector<node>> nodes;

	std::map<int, node*> id_to_node;
};

struct pathState
{
	long long cost;

	node* state_node;

	direction state_direction;

	pathState(long long cost_, node* state_node_, direction state_direction_)
	{
		cost = cost_;
		state_node = state_node_;
		state_direction = state_direction_;
	}

	pathState(long long cost_, node* state_node_, direction state_direction_, std::set<int> path_)
	{
		cost = cost_;
		state_node = state_node_;
		state_direction = state_direction_;
		path = path_;
	}

	std::set<int> path;

	bool operator>(const pathState& other) const
	{
		return cost > other.cost;
	}
};


graph loadGraph(std::string input_file, int num_bytes, int grid_max);

std::vector<std::pair<int, int>> loadBytes(std::string input_file);


node* getGraphNode(std::vector<std::vector<node>>& graph, int i, int j);


long long findShortestPathLength(graph& the_graph);

std::pair<int, int> findFirstBlockingByte(graph& the_graph, std::vector<std::pair<int, int>>& bytes, int starting_index);