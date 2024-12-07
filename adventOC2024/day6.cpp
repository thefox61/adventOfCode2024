#include "day6.h"
#include <unordered_set>


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
			if (temp[i] == '^')
			{
				std::cout << "Guard starting position: " << map.size() << " " << i << std::endl;
			}
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

			if (temp[i] == '^')
			{
				root_node_index = i;
			}
		}
		graph.emplace_back(new_row);
		
		if (root_node_index != -1)
		{
			root_node = &graph[graph.size() - 1][root_node_index];

			root_node_index = -1;
		}
	}

	// update node relationships
	for (int i = 0; i < graph.size(); i++)
	{
		for (int j = 0; j < graph[i].size(); j++)
		{
			node* curr_node = getGraphIndex(i, j, graph);

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
	

	return true;
}

char getMapIndex(int i, int j, std::vector<std::vector<char>>& map)
{
	if (i >= map.size() || j >= map[i].size())
	{
		return 'F';
	}

	return map[i][j];
}

node* getGraphIndex(int i, int j, std::vector<std::vector<node>>& graph)
{
	if (i >= graph.size() || j >= graph[i].size())
	{
		return NULL;
	}

	return &graph[i][j];
}

int countDistinctPath(node* starting_node, std::vector<std::vector<node>>& graph)
{
	direction curr_direction = UP;
	int count = 0;

	node* curr_node = starting_node;

	curr_node->value = 'X';
	count++;

	while (curr_node)
	{
		switch (curr_direction)
		{
			case direction::UP:
				if (curr_node->up)
				{
					if (curr_node->up->value != '#')
					{
						curr_node = curr_node->up;

						if (curr_node->value != 'X')
						{
							count++;
							curr_node->value = 'X';
						}
						
					}
					else
					{
						curr_direction = RIGHT;
					}
				}
				else
				{
					curr_node = curr_node->up;
				}
				break;
			case direction::RIGHT:
				if (curr_node->right)
				{
					if (curr_node->right->value != '#')
					{
						curr_node = curr_node->right;
						if (curr_node->value != 'X')
						{
							count++;
							curr_node->value = 'X';
						}
					}
					else
					{
						curr_direction = DOWN;
					}
				}
				else
				{
					curr_node = curr_node->right;
				}
				break;
			case direction::DOWN:
				if (curr_node->down)
				{
					if (curr_node->down->value != '#')
					{
						curr_node = curr_node->down;
						if (curr_node->value != 'X')
						{
							count++;
							curr_node->value = 'X';
						}
					}
					else
					{
						curr_direction = LEFT;
					}
				}
				else
				{
					curr_node = curr_node->down;
				}
				break;
			case direction::LEFT:
				if (curr_node->left)
				{
					if (curr_node->left->value != '#')
					{
						curr_node = curr_node->left;

						
						if (curr_node->value != 'X')
						{
							count++;
							curr_node->value = 'X';
						}
					}
					else
					{
						curr_direction = UP;
					}
				}
				else
				{
					curr_node = curr_node->left;
				}

				break;
		}

		 
	}
	return count;
}

int countObstacleLocations(node* starting_node, std::vector<std::vector<node>>& graph)
{
	direction curr_direction = UP;
	int count = 0;

	node* curr_node = starting_node;

	curr_node->value = 'X';

	while (curr_node)
	{
		switch (curr_direction)
		{
		case direction::UP:
			if (curr_node->up)
			{
				if (curr_node->up->value != '#')
				{
					// check loop
					if (curr_node->up->value != 'X')
					{
						char curr_node_value = curr_node->up->value;
						curr_node->up->value = '#';
						if (checkLoop(curr_node, curr_direction, graph))
						{
							count++;
						}

						curr_node->up->value = curr_node_value;
					}
					

					curr_node = curr_node->up;

					if (curr_node->value != 'X')
					{
						//count++;
						curr_node->value = 'X';
					}

				}
				else
				{
					curr_direction = RIGHT;
				}
			}
			else
			{
				curr_node = curr_node->up;
			}
			break;
		case direction::RIGHT:
			if (curr_node->right)
			{
				if (curr_node->right->value != '#')
				{
					// check loop
					if (curr_node->right->value != 'X')
					{
						char curr_node_value = curr_node->right->value;
						curr_node->right->value = '#';
						if (checkLoop(curr_node, curr_direction, graph))
						{
							count++;
						}
						curr_node->right->value = curr_node_value;
					}
					

					curr_node = curr_node->right;
					if (curr_node->value != 'X')
					{
						//count++;
						curr_node->value = 'X';
					}
				}
				else
				{
					curr_direction = DOWN;
				}
			}
			else
			{
				curr_node = curr_node->right;
			}
			break;
		case direction::DOWN:
			if (curr_node->down)
			{
				if (curr_node->down->value != '#')
				{
					// check loop
					if (curr_node->down->value != 'X')
					{
						char curr_node_value = curr_node->down->value;
						curr_node->down->value = '#';
						if (checkLoop(curr_node, curr_direction, graph))
						{
							count++;
						}
						curr_node->down->value = curr_node_value;
					}
					

					curr_node = curr_node->down;
					if (curr_node->value != 'X')
					{
						//count++;
						curr_node->value = 'X';
					}
				}
				else
				{
					curr_direction = LEFT;
				}
			}
			else
			{
				curr_node = curr_node->down;
			}
			break;
		case direction::LEFT:
			if (curr_node->left)
			{
				if (curr_node->left->value != '#')
				{
					// check loop
					if (curr_node->left->value != 'X')
					{
						char curr_node_value = curr_node->left->value;
						curr_node->left->value = '#';
						if (checkLoop(curr_node, curr_direction, graph))
						{
							count++;
						}
						curr_node->left->value = curr_node_value;
					}
					

					curr_node = curr_node->left;


					if (curr_node->value != 'X')
					{
						//count++;
						curr_node->value = 'X';
					}
				}
				else
				{
					curr_direction = UP;
				}
			}
			else
			{
				curr_node = curr_node->left;
			}

			break;
		}


	}
	return count;
}

bool checkLoop(node* starting_node, direction starting_direction, std::vector<std::vector<node>>& graph)
{
	direction curr_direction = starting_direction;

	std::unordered_set<int> visited_nodes;

	std::unordered_map<int, std::vector<direction>> visited_nodes_direction;


	node* curr_node = starting_node;

	curr_node->value = 'X';
	//count++;

	while (curr_node)
	{
		switch (curr_direction)
		{
		case direction::UP:
			if (curr_node->up)
			{
				if (curr_node->up->value != '#')
				{
					curr_node = curr_node->up;

					if (visited_nodes.count(curr_node->id) > 0)
					{
						for (int i = 0; i < visited_nodes_direction[curr_node->id].size(); i++)
						{
							if (visited_nodes_direction[curr_node->id][i] == curr_direction)
							{
								return true;
							}
						}
						visited_nodes_direction[curr_node->id].emplace_back(curr_direction);
					}
					else
					{
						visited_nodes.insert(curr_node->id);
						visited_nodes_direction[curr_node->id].emplace_back(curr_direction);
					}

				}
				else
				{
					curr_direction = RIGHT;
				}
			}
			else
			{
				curr_node = curr_node->up;
			}
			break;
		case direction::RIGHT:
			if (curr_node->right)
			{
				if (curr_node->right->value != '#')
				{
					curr_node = curr_node->right;

					if (visited_nodes.count(curr_node->id) > 0)
					{
						for (int i = 0; i < visited_nodes_direction[curr_node->id].size(); i++)
						{
							if (visited_nodes_direction[curr_node->id][i] == curr_direction)
							{
								return true;
							}
						}
						visited_nodes_direction[curr_node->id].emplace_back(curr_direction);
					}
					else
					{
						visited_nodes.insert(curr_node->id);
						visited_nodes_direction[curr_node->id].emplace_back(curr_direction);
					}
				}
				else
				{
					curr_direction = DOWN;
				}
			}
			else
			{
				curr_node = curr_node->right;
			}
			break;
		case direction::DOWN:
			if (curr_node->down)
			{
				if (curr_node->down->value != '#')
				{
					curr_node = curr_node->down;

					if (visited_nodes.count(curr_node->id) > 0)
					{
						for (int i = 0; i < visited_nodes_direction[curr_node->id].size(); i++)
						{
							if (visited_nodes_direction[curr_node->id][i] == curr_direction)
							{
								return true;
							}
						}
						visited_nodes_direction[curr_node->id].emplace_back(curr_direction);
					}
					else
					{
						visited_nodes.insert(curr_node->id);
						visited_nodes_direction[curr_node->id].emplace_back(curr_direction);
					}
				}
				else
				{
					curr_direction = LEFT;
				}
			}
			else
			{
				curr_node = curr_node->down;
			}
			break;
		case direction::LEFT:
			if (curr_node->left)
			{
				if (curr_node->left->value != '#')
				{
					curr_node = curr_node->left;

					if (visited_nodes.count(curr_node->id) > 0)
					{
						for (int i = 0; i < visited_nodes_direction[curr_node->id].size(); i++)
						{
							if (visited_nodes_direction[curr_node->id][i] == curr_direction)
							{
								return true;
							}
						}
						visited_nodes_direction[curr_node->id].emplace_back(curr_direction);
					}
					else
					{
						visited_nodes.insert(curr_node->id);
						visited_nodes_direction[curr_node->id].emplace_back(curr_direction);
					}
				}
				else
				{
					curr_direction = UP;
				}
			}
			else
			{
				curr_node = curr_node->left;
			}

			break;
		}


	}
	return false;
}


