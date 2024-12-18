#pragma once

// save time includes
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <unordered_map>
#include <set>

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


struct reindeer
{
	node* curr_node;
	direction curr_direction = direction::EAST;

	node* end_node;

	std::unordered_map<int, node*> id_to_node;
};

std::vector<std::vector<node>> loadGraph(std::string input_file, reindeer& the_reindeer);

node* getGraphNode(std::vector<std::vector<node>>& graph, int i, int j);

long calculateShortestPath(std::vector<std::vector<node>>& graph, reindeer& the_reindeer);


long calculateNodesShortestPaths(std::vector<std::vector<node>>& graph, reindeer& the_reindeer);

node* minCost(reindeer& the_reindeer, std::unordered_map<int, int>& lowest_cost, std::unordered_map<int, bool>& visited);

std::pair<direction, direction> getPerpendicularDirections(direction curr_direction);

bool validDirection(node* the_node, direction desired_direction);

node* getNode(node* the_node, direction desired_direction);