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

	char value = '0';

	node(char c, int node_id)
	{
		value = c;
		id = node_id;
	}

	bool processed = false;

	int column = -1;
	int row = -1;
};


std::vector<std::vector<char>> loadMap(std::string input_file);

bool loadGraph(std::string input_file, node*& root_node, std::vector<std::vector<node>>& graph);

node* getGraphIndex(int i, int j, std::vector<std::vector<node>>& graph);

long long calculateFenceCost(node* root_node, std::vector<std::vector<node>>& graph);

long long calculateFenceCostBulk(node* root_node, std::vector<std::vector<node>>& graph);

long long calculateAreaCost(node* starting_node);

long long calculateAreaCostPerimeter(node* starting_node);

void calculatePerimeterAndArea(node* node, long& perimeter, long& area);

void calculateSidesAndArea(node* node, std::unordered_map<int, std::vector<int>>& row_sides_top, std::unordered_map<int, std::vector<int>>& row_sides_bottom, std::unordered_map<int, std::vector<int>>& column_sides_left, std::unordered_map<int, std::vector<int>>& column_sides_right, long& area);

long long countSides(std::unordered_map<int, std::vector<int>>& sides_map);









