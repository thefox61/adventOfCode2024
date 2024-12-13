#include "day12.h"
#include <algorithm>

std::vector<std::vector<char>> loadMap(std::string input_file)
{
	std::ifstream the_file(input_file);
	std::string temp;

	std::vector<std::vector<char>> map;

	while (std::getline(the_file, temp))
	{
		std::vector<char> new_row;
		for (int i = 0; i < temp.length(); i++)
		{
			new_row.emplace_back(temp[i]);
		}
		map.emplace_back(new_row);
	}

	return map;
}


bool loadGraph(std::string input_file, node*& root_node, std::vector<std::vector<node>>& graph)
{
	std::ifstream the_file(input_file);
	std::string temp;

	int id_count = 0;

	int root_node_index = -1;

	while (std::getline(the_file, temp))
	{
		std::vector<node> new_row;
		for (int i = 0; i < temp.length(); i++)
		{
			new_row.emplace_back(temp[i], id_count);
			id_count++;
		}
		graph.emplace_back(new_row);
	}

	// update node relationships
	for (int i = 0; i < graph.size(); i++)
	{
		for (int j = 0; j < graph[i].size(); j++)
		{
			node* curr_node = getGraphIndex(i, j, graph);

			curr_node->row = i;
			curr_node->column = j;

			// up
			curr_node->up = getGraphIndex(i - 1, j, graph);
			// right
			curr_node->right = getGraphIndex(i, j + 1, graph);
			// down
			curr_node->down = getGraphIndex(i + 1, j, graph);
			// left
			curr_node->left = getGraphIndex(i, j - 1, graph);
		}
	}

	root_node = &graph[0][0];

	return true;
}

node* getGraphIndex(int i, int j, std::vector<std::vector<node>>& graph)
{
	if (i >= graph.size() || j >= graph[i].size())
	{
		return NULL;
	}

	return &graph[i][j];
}

long long calculateFenceCost(node* root_node, std::vector<std::vector<node>>& graph)
{
	long long cost = 0;

	for (int i = 0; i < graph.size(); i++)
	{
		for (int j = 0; j < graph[i].size(); j++)
		{
			cost += calculateAreaCost(&graph[i][j]);
		}
	}
	return cost;
}

long long calculateFenceCostBulk(node* root_node, std::vector<std::vector<node>>& graph)
{
	long long cost = 0;

	for (int i = 0; i < graph.size(); i++)
	{
		for (int j = 0; j < graph[i].size(); j++)
		{
			cost += calculateAreaCostPerimeter(&graph[i][j]);
		}
	}
	return cost;
}

long long calculateAreaCost(node* starting_node)
{
	long long areaCost = 0;
	long perimeter = 0;
	long area = 0;


	if (!starting_node->processed)
	{
		calculatePerimeterAndArea(starting_node, perimeter, area);
	}

	areaCost = perimeter * area;

	return areaCost;
}

long long calculateAreaCostPerimeter(node* starting_node)
{
	long long cost = 0;

	long area = 0;

	long sides = 0;

	// row maps key is the row index (-1 is top and length + 1 is bottom), vector stores all columns that have an edge at this index
	std::unordered_map<int, std::vector<int>> row_sides_top;
	std::unordered_map<int, std::vector<int>> row_sides_bottom;

	// column maps key is the column index (-1 is top and length + 1 is bottom), vector stores all rows that have an edge at this index
	std::unordered_map<int, std::vector<int>> column_sides_left;
	std::unordered_map<int, std::vector<int>> column_sides_right;

	if (!starting_node->processed)
	{
		calculateSidesAndArea(starting_node, row_sides_top, row_sides_bottom, column_sides_left, column_sides_right, area);
	}

	// iterate through all maps
	// for each row/column check how many consecutive sequences of indexes are there, each one corresponds to a side

	sides += countSides(row_sides_top);
	sides += countSides(row_sides_bottom);
	sides += countSides(column_sides_left);
	sides += countSides(column_sides_right);

	
	cost = area * sides;

	return cost;
}

void calculatePerimeterAndArea(node* node, long& perimeter, long& area)
{
	area += 1;

	node->processed = true;

	if (node->up && node->up->value == node->value)
	{
		if (!node->up->processed)
		{
			calculatePerimeterAndArea(node->up, perimeter, area);
		}
	}
	else
	{
		perimeter++;
	}

	if (node->down && node->down->value == node->value)
	{
		if (!node->down->processed)
		{
			calculatePerimeterAndArea(node->down, perimeter, area);
		}
	}
	else
	{
		perimeter++;
	}

	if (node->left && node->left->value == node->value)
	{
		if (!node->left->processed)
		{
			calculatePerimeterAndArea(node->left, perimeter, area);
		}
	}
	else
	{
		perimeter++;
	}

	if (node->right && node->right->value == node->value)
	{
		if (!node->right->processed)
		{
			calculatePerimeterAndArea(node->right, perimeter, area);
		}
	}
	else
	{
		perimeter++;
	}

}

void calculateSidesAndArea(node* node, std::unordered_map<int, std::vector<int>>& row_sides_top, std::unordered_map<int, std::vector<int>>& row_sides_bottom, std::unordered_map<int, std::vector<int>>& column_sides_left, std::unordered_map<int, std::vector<int>>& column_sides_right, long& area)
{
	area += 1;

	node->processed = true;

	if (node->up && node->up->value == node->value)
	{
		if (!node->up->processed)
		{
			calculateSidesAndArea(node->up, row_sides_top, row_sides_bottom, column_sides_left, column_sides_right, area);
		}
	}
	else
	{
		row_sides_top[node->row - 1].emplace_back(node->column);
	}

	if (node->down && node->down->value == node->value)
	{
		if (!node->down->processed)
		{
			calculateSidesAndArea(node->down, row_sides_top, row_sides_bottom, column_sides_left, column_sides_right, area);
		}

	}
	else
	{
		row_sides_bottom[node->row + 1].emplace_back(node->column);
	}

	if (node->left && node->left->value == node->value)
	{
		if (!node->left->processed)
		{
			calculateSidesAndArea(node->left, row_sides_top, row_sides_bottom, column_sides_left, column_sides_right, area);
		}
	}
	else
	{
		column_sides_left[node->column - 1].emplace_back(node->row);
	}

	if (node->right && node->right->value == node->value)
	{
		if (!node->right->processed)
		{
			calculateSidesAndArea(node->right, row_sides_top, row_sides_bottom, column_sides_left, column_sides_right, area);
		}

	}
	else
	{
		column_sides_right[node->column + 1].emplace_back(node->row);
	}

}

long long countSides(std::unordered_map<int, std::vector<int>>& sides_map)
{
	long long sides = 0;
	std::unordered_map<int, std::vector<int>>::iterator sides_it = sides_map.begin();

	while (sides_it != sides_map.end())
	{
		std::vector<int>& curr_index = sides_it->second;

		if (curr_index.empty())
		{
			continue;
		}

		std::sort(curr_index.begin(), curr_index.end());

		int last = curr_index[0];
		sides++;

		for (int i = 1; i < curr_index.size(); i++)
		{
			if (curr_index[i] != last + 1)
			{
				sides++;
			}
			last = curr_index[i];
		}

		sides_it++;
	}

	return sides;
}
