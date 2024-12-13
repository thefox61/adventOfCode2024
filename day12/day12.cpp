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

	std::unordered_map<int, std::vector<int>> row_sides_top;
	std::unordered_map<int, std::vector<int>> column_sides_left;
	std::unordered_map<int, std::vector<int>> row_sides_bottom;
	std::unordered_map<int, std::vector<int>> column_sides_right;

	if (!starting_node->processed)
	{
		calculateSidesAndArea(starting_node, row_sides_top, row_sides_bottom, column_sides_left, column_sides_right, area);
	}

	std::unordered_map<int, std::vector<int>>::iterator row_top_it = row_sides_top.begin();
	std::unordered_map<int, std::vector<int>>::iterator row_bottom_it = row_sides_bottom.begin();
	std::unordered_map<int, std::vector<int>>::iterator column_left_it = column_sides_left.begin();
	std::unordered_map<int, std::vector<int>>::iterator column_right_it = column_sides_right.begin();

	while (row_top_it != row_sides_top.end())
	{
		std::vector<int>& curr_row = row_top_it->second;

		if (curr_row.empty())
		{
			continue;
		}

		std::sort(curr_row.begin(), curr_row.end());

		int last = curr_row[0];
		sides++;

		for (int i = 1; i < curr_row.size(); i++)
		{
			if (curr_row[i] != last + 1)
			{
				sides++;
			}
			last = curr_row[i];
		}

		row_top_it++;
	}

	while (row_bottom_it != row_sides_bottom.end())
	{
		std::vector<int>& curr_row = row_bottom_it->second;

		if (curr_row.empty())
		{
			continue;
		}

		std::sort(curr_row.begin(), curr_row.end());

		int last = curr_row[0];
		sides++;

		for (int i = 1; i < curr_row.size(); i++)
		{
			if (curr_row[i] != last + 1)
			{
				sides++;
			}
			last = curr_row[i];
		}

		row_bottom_it++;
	}

	while (column_left_it != column_sides_left.end())
	{
		std::vector<int>& curr_column = column_left_it->second;

		if (curr_column.empty())
		{
			continue;
		}

		std::sort(curr_column.begin(), curr_column.end());

		int last = curr_column[0];
		sides++;

		for (int i = 1; i < curr_column.size(); i++)
		{
			if (curr_column[i] != last + 1)
			{
				sides++;
			}
			last = curr_column[i];
		}

		column_left_it++;
	}

	while (column_right_it != column_sides_right.end())
	{
		std::vector<int>& curr_column = column_right_it->second;

		if (curr_column.empty())
		{
			continue;
		}

		std::sort(curr_column.begin(), curr_column.end());

		int last = curr_column[0];
		sides++;

		for (int i = 1; i < curr_column.size(); i++)
		{
			if (curr_column[i] != last + 1)
			{
				sides++;
			}
			last = curr_column[i];
		}

		column_right_it++;
	}


	cost = area * sides;

	return cost;
}

void calculatePerimeterAndArea(node* node, long& perimeter, long& area)
{
	area += 1;

	node->processed = true;

	if (node->up && node->up->value == node->value)
	{
		//areaCost += calculateAreaCost(starting_node->up, perimeter, area);

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
		//areaCost += calculateAreaCost(starting_node->up, perimeter, area);

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
		//areaCost += calculateAreaCost(starting_node->up, perimeter, area);

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
		//areaCost += calculateAreaCost(starting_node->up, perimeter, area);

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
		//areaCost += calculateAreaCost(starting_node->up, perimeter, area);

		if (!node->up->processed)
		{
			calculateSidesAndArea(node->up, row_sides_top, row_sides_bottom, column_sides_left, column_sides_right, area);
		}

	}
	else
	{
		//perimeter++;
		row_sides_top[node->row - 1].emplace_back(node->column);
	}

	if (node->down && node->down->value == node->value)
	{
		//areaCost += calculateAreaCost(starting_node->up, perimeter, area);

		if (!node->down->processed)
		{
			calculateSidesAndArea(node->down, row_sides_top, row_sides_bottom, column_sides_left, column_sides_right, area);
		}

	}
	else
	{
		//perimeter++;
		row_sides_bottom[node->row + 1].emplace_back(node->column);
	}

	if (node->left && node->left->value == node->value)
	{
		//areaCost += calculateAreaCost(starting_node->up, perimeter, area);

		if (!node->left->processed)
		{
			calculateSidesAndArea(node->left, row_sides_top, row_sides_bottom, column_sides_left, column_sides_right, area);
		}

	}
	else
	{
		//perimeter++;
		column_sides_left[node->column - 1].emplace_back(node->row);
	}

	if (node->right && node->right->value == node->value)
	{
		//areaCost += calculateAreaCost(starting_node->up, perimeter, area);

		if (!node->right->processed)
		{
			calculateSidesAndArea(node->right, row_sides_top, row_sides_bottom, column_sides_left, column_sides_right, area);
		}

	}
	else
	{
		//perimeter++;
		column_sides_right[node->column + 1].emplace_back(node->row);
	}

}
