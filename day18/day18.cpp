#include "day18.h"
#include <queue>

graph loadGraph(std::string input_file, int num_bytes, int grid_max)
{

    std::ifstream the_file(input_file);

    std::string temp;

    graph the_graph;
    the_graph.nodes = std::vector<std::vector<node>>(grid_max, std::vector<node>(grid_max, node('.', grid_max)));

    for (int i = 0; i < num_bytes; i++)
    {
        std::getline(the_file, temp);

        int comma_loc = temp.find_first_of(',');
        
        int y = std::stoi(temp.substr(0, comma_loc));
        int x = std::stoi(temp.substr(comma_loc + 1, temp.length() - comma_loc + 1));

        the_graph.nodes[x][y].value = '#';
    }

    int id_count= 0;
    for (int i = 0; i < the_graph.nodes.size(); i++)
    {
        for (int j = 0; j < the_graph.nodes[i].size(); j++)
        {
            the_graph.nodes[i][j].id = id_count;

            the_graph.nodes[i][j].north = getGraphNode(the_graph.nodes, i - 1, j);
            the_graph.nodes[i][j].east = getGraphNode(the_graph.nodes, i, j + 1);
            the_graph.nodes[i][j].south = getGraphNode(the_graph.nodes, i + 1, j);
            the_graph.nodes[i][j].west = getGraphNode(the_graph.nodes, i, j - 1);

            the_graph.id_to_node[id_count] = &the_graph.nodes[i][j];

            id_count++;
        }
    }
    
    return the_graph;
}

std::vector<std::pair<int, int>> loadBytes(std::string input_file)
{
    std::ifstream the_file(input_file);

    std::string temp;

    std::vector<std::pair<int, int>> bytes;

    while(std::getline(the_file, temp))
    {

        int comma_loc = temp.find_first_of(',');

        int y = std::stoi(temp.substr(0, comma_loc));
        int x = std::stoi(temp.substr(comma_loc + 1, temp.length() - comma_loc + 1));

        //the_graph.nodes[x][y].value = '#';
        bytes.emplace_back(x, y);
    }

    return bytes;
}


node* getGraphNode(std::vector<std::vector<node>>& graph, int i, int j)
{
    if (i < 0 || i >= graph.size() || j < 0 || j >= graph[i].size())
    {
        return NULL;
    }

    if (graph[i][j].value == '#')
    {
        return NULL;
    }

    return &graph[i][j];
}

long long findShortestPathLength(graph& the_graph)
{
    std::map<std::pair<int, direction>, long> lowest_cost;

    std::priority_queue<pathState, std::vector<pathState>, std::greater<pathState>> queue;

    queue.push(pathState(0, &the_graph.nodes[0][0],direction::NORTH));
    queue.push(pathState(0, &the_graph.nodes[0][0], direction::EAST));
    queue.push(pathState(0, &the_graph.nodes[0][0], direction::SOUTH));
    queue.push(pathState(0, &the_graph.nodes[0][0], direction::WEST));

    while (!queue.empty())
    {
        pathState curr_state = queue.top();
        queue.pop();

        std::pair<int, direction> curr_pair = std::make_pair(curr_state.state_node->id, curr_state.state_direction);

        if (lowest_cost.count(curr_pair)
            && curr_state.cost >= lowest_cost[curr_pair])
        {
            continue;
        }

        lowest_cost[curr_pair] = curr_state.cost;

        if (curr_state.state_node->north && curr_state.state_node->north->value != '#')
        {
            queue.push(pathState(curr_state.cost + 1, curr_state.state_node->north, direction::NORTH));
        }
        if (curr_state.state_node->east && curr_state.state_node->east->value != '#')
        {
            queue.push(pathState(curr_state.cost + 1, curr_state.state_node->east, direction::EAST));
        }
        if (curr_state.state_node->south && curr_state.state_node->south->value != '#')
        {
            queue.push(pathState(curr_state.cost + 1, curr_state.state_node->south, direction::SOUTH));
        }
        if (curr_state.state_node->west && curr_state.state_node->west->value != '#')
        {
            queue.push(pathState(curr_state.cost + 1, curr_state.state_node->west, direction::WEST));
        }

    }
    long end_cost = LONG_MAX;

    node* goal_node = &the_graph.nodes[the_graph.nodes.size() - 1][the_graph.nodes.size() - 1];

    if (lowest_cost.count(std::make_pair(goal_node->id, direction::NORTH)) > 0)
    {
        end_cost = std::min(end_cost, lowest_cost[std::make_pair(goal_node->id, direction::NORTH)]);
    }
    if (lowest_cost.count(std::make_pair(goal_node->id, direction::EAST)) > 0)
    {
        end_cost = std::min(end_cost, lowest_cost[std::make_pair(goal_node->id, direction::EAST)]);
    }
    if (lowest_cost.count(std::make_pair(goal_node->id, direction::SOUTH)) > 0)
    {
        end_cost = std::min(end_cost, lowest_cost[std::make_pair(goal_node->id, direction::SOUTH)]);
    }
    if (lowest_cost.count(std::make_pair(goal_node->id, direction::WEST)) > 0)
    {
        end_cost = std::min(end_cost, lowest_cost[std::make_pair(goal_node->id, direction::WEST)]);
    }

    return end_cost;
}

std::pair<int, int> findFirstBlockingByte(graph& the_graph, std::vector<std::pair<int, int>>& bytes, int starting_index)
{
    long cost = findShortestPathLength(the_graph);

    std::pair<int, int> curr_byte = bytes[starting_index];

    while (cost != LONG_MAX)
    {
        curr_byte = bytes[starting_index];
        the_graph.nodes[curr_byte.first][curr_byte.second].value = '#';

        cost = findShortestPathLength(the_graph);

        starting_index++;
    }

    return curr_byte;
}
