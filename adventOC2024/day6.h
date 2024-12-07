#pragma once


// save time includes
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <unordered_map>


struct node
{
	int id;
	node* up = NULL;
	node* right = NULL;
	node* down = NULL;
	node* left = NULL;

	char value = 'F';

	node(char c, int node_id)
	{
		value = c;
		id = node_id;
	}


};

enum direction
{
	UP = 0,
	RIGHT = 1,
	DOWN = 2,
	LEFT = 3
};


std::vector<std::vector<char>> loadMap(std::string input_file);

bool loadGraph(std::string input_file, node*& root_node, std::vector<std::vector<node>>& graph);


char getMapIndex(int i, int j, std::vector<std::vector<char>>& map);

node* getGraphIndex(int i, int j, std::vector<std::vector<node>>& graph);

int countDistinctPath(node* starting_node,  std::vector<std::vector<node>>& graph);

int countObstacleLocations(node* starting_node, std::vector<std::vector<node>>& graph);

bool checkLoop(node* starting_node, direction starting_direction, std::vector<std::vector<node>>& graph);