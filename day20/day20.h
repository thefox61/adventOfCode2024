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

struct node
{
	unsigned int id;

	node* north = NULL;
	node* east = NULL;
	node* west = NULL;
	node* south = NULL;

	char value;


	std::pair<int, int> position;

	node(char value_, unsigned int id_)
	{
		value = value_;

		id = id_;
	}

	long path_index = -1;

};


struct graph
{
	std::vector<std::vector<node>> nodes;

	std::map<int, node*> id_to_node;

	node* start_node;
	node* end_node;
};

enum class direction
{
	NORTH,
	EAST,
	WEST,
	SOUTH
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

	pathState(long long cost_, node* state_node_, direction state_direction_, std::set<int> path_, std::vector<int> ordered_path_)
	{
		cost = cost_;
		state_node = state_node_;
		state_direction = state_direction_;
		path = path_;
		ordered_path = ordered_path_;
	}

	std::set<int> path;

	std::vector<int> ordered_path;

	bool operator>(const pathState& other) const
	{
		return cost > other.cost;
	}

};

graph loadGraph(std::string input_file);

node* getGraphNode(std::vector<std::vector<node>>& graph, int i, int j, bool return_walls = false);

long countNumCheats(graph& the_graph);

long long findShortestPathLength(graph& the_graph, std::vector<int>& final_path);

long checkCheat(node* path_node, node* cheat_node, direction node_direction);


long long checkAllCheats(graph& the_graph, std::vector<int>& final_path, long threshold);

long long checkAllCheatsPart2(graph& the_graph, std::vector<int>& final_path, long threshold);

int checkNodeCheats(node* path_node, node* cheat_node, long threshold);

long calculateDistance(node* node1, node* node2);