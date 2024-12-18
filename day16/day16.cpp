#include "day16.h"
#include "limits.h"
#include <queue>
#include <map>

std::vector<std::vector<node>> loadGraph(std::string input_file, reindeer& the_reindeer)
{
    std::ifstream the_file(input_file);

    std::string temp;

    std::vector<std::vector<node>> graph;
    int id_count = 0;
    while (std::getline(the_file, temp))
    {
        std::vector<node> curr_row;
        for (int i = 0; i < temp.length(); i++)
        {
            curr_row.emplace_back(temp[i], id_count);
            id_count++;
        }

        graph.emplace_back(curr_row);
    }

    for (int i = 0; i < graph.size(); i++)
    {
        for (int j = 0; j < graph[i].size(); j++)
        {
            if (graph[i][j].value == 'S')
            {
                the_reindeer.curr_node = &graph[i][j];
            }
            else if (graph[i][j].value == 'E')
            {
                the_reindeer.end_node = &graph[i][j];
            }

            graph[i][j].north = getGraphNode(graph, i - 1, j); 
            graph[i][j].east = getGraphNode(graph, i, j + 1);
            graph[i][j].south = getGraphNode(graph, i + 1, j);
            graph[i][j].west = getGraphNode(graph, i, j - 1);

            the_reindeer.id_to_node[graph[i][j].id] = &graph[i][j];
        }
    }

    return graph;
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

long calculateShortestPath(std::vector<std::vector<node>>& graph, reindeer& the_reindeer)
{
    std::map<std::pair<int, direction>, long> lowest_cost;
    
    std::priority_queue<pathState, std::vector<pathState>, std::greater<pathState>> queue;

    

    queue.push(pathState(0, the_reindeer.curr_node, the_reindeer.curr_direction));

    std::pair<direction, direction> rotations = getPerpendicularDirections(the_reindeer.curr_direction);

    /*queue.push(pathState(1000, the_reindeer.curr_node, rotations.first));
    queue.push(pathState(1000, the_reindeer.curr_node, rotations.second));*/

    while(!queue.empty())
    {
        pathState curr_state = queue.top();
        queue.pop();
        
        std::pair<int, direction> curr_pair = std::make_pair(curr_state.state_node->id, curr_state.state_direction);

        if(lowest_cost.count(curr_pair)
            && curr_state.cost >= lowest_cost[curr_pair])
        {
            continue;
        }
        lowest_cost[curr_pair] = curr_state.cost;

        if (validDirection(curr_state.state_node, curr_state.state_direction))
        {
            queue.push(pathState(curr_state.cost + 1, getNode(curr_state.state_node, curr_state.state_direction), curr_state.state_direction));
        }


        rotations = getPerpendicularDirections(curr_state.state_direction);

        queue.push(pathState(curr_state.cost + 1000, curr_state.state_node, rotations.first));
        queue.push(pathState(curr_state.cost + 1000, curr_state.state_node, rotations.second));


    }

    long end_cost = LONG_MAX;

    if (the_reindeer.end_node->north)
    {
        end_cost = std::min(end_cost, lowest_cost[std::make_pair(the_reindeer.end_node->id, direction::NORTH)]);
    }
    if (the_reindeer.end_node->east)
    {
        end_cost = std::min(end_cost, lowest_cost[std::make_pair(the_reindeer.end_node->id, direction::EAST)]);
    }
    if (the_reindeer.end_node->south)
    {
        end_cost = std::min(end_cost, lowest_cost[std::make_pair(the_reindeer.end_node->id, direction::SOUTH)]);
    }
    if (the_reindeer.end_node->west)
    {
        end_cost = std::min(end_cost, lowest_cost[std::make_pair(the_reindeer.end_node->id, direction::WEST)]);
    }

    return end_cost - 1000;
    // return lowest_cost[the_reindeer.end_node->id];
}

long calculateNodesShortestPaths(std::vector<std::vector<node>>& graph, reindeer& the_reindeer)
{
    std::map<std::pair<int, direction>, long> lowest_cost;

    std::priority_queue<pathState, std::vector<pathState>, std::greater<pathState>> queue;

    std::set<int> nodes_in_end_path;

    long best_end_cost = LONG_MAX;



    queue.push(pathState(0, the_reindeer.curr_node, the_reindeer.curr_direction));

    std::pair<direction, direction> rotations = getPerpendicularDirections(the_reindeer.curr_direction);


    while (!queue.empty())
    {
        pathState curr_state = queue.top();
        queue.pop();

        std::set<int> path = curr_state.path;
        path.insert(curr_state.state_node->id);

        if (curr_state.state_node->id == the_reindeer.end_node->id && best_end_cost >= curr_state.cost)
        {
            best_end_cost = curr_state.cost;
            std::set<int>::iterator it = path.begin();
            while (it != path.end())
            {
                nodes_in_end_path.insert(*it);
                it++;
            }
        }

        std::pair<int, direction> curr_pair = std::make_pair(curr_state.state_node->id, curr_state.state_direction);

        if (lowest_cost.count(curr_pair)
            && curr_state.cost > lowest_cost[curr_pair])
        {
            continue;
        }
        lowest_cost[curr_pair] = curr_state.cost;

        if (validDirection(curr_state.state_node, curr_state.state_direction))
        {
            queue.push(pathState(curr_state.cost + 1, getNode(curr_state.state_node, curr_state.state_direction), curr_state.state_direction, path));
        }


        rotations = getPerpendicularDirections(curr_state.state_direction);

        queue.push(pathState(curr_state.cost + 1000, curr_state.state_node, rotations.first, path));
        queue.push(pathState(curr_state.cost + 1000, curr_state.state_node, rotations.second, path));


    }
    return nodes_in_end_path.size();
}

node* minCost(reindeer& the_reindeer, std::unordered_map<int, int>& lowest_cost, std::unordered_map<int, bool>& visited)
{
    int min_cost = INT_MAX;

    node* closest_node = NULL;

    std::unordered_map<int, int>::iterator cost_it = lowest_cost.begin();

    while (cost_it != lowest_cost.end())
    {
        if (cost_it->second < min_cost && !visited[cost_it->first])
        {
            min_cost = cost_it->second;
            closest_node = the_reindeer.id_to_node[cost_it->first];
        }
        cost_it++;
    }
    
    return closest_node;
}

std::pair<direction, direction> getPerpendicularDirections(direction curr_direction)
{
    switch (curr_direction)
    {
    case direction::NORTH:
        return std::make_pair(direction::EAST, direction::WEST);

    case direction::EAST:
        return std::make_pair(direction::NORTH, direction::SOUTH);

    case direction::SOUTH:
        return std::make_pair(direction::EAST, direction::WEST);
    
    case direction::WEST:
        return std::make_pair(direction::NORTH, direction::SOUTH);

    }
    return std::make_pair(direction::NORTH, direction::SOUTH);
}

bool validDirection(node* the_node, direction desired_direction)
{
    switch (desired_direction)
    {
    case direction::NORTH:
        if (the_node->north)
        {
            return true;
        }
        break;

    case direction::EAST:
        if (the_node->east)
        {
            return true;
        }
        break;

    case direction::SOUTH:
        if (the_node->south)
        {
            return true;
        }
        break;

    case direction::WEST:
        if (the_node->west)
        {
            return true;
        }
        break;

    }
    return false;
}

node* getNode(node* the_node, direction desired_direction)
{
    switch (desired_direction)
    {
    case direction::NORTH:
        return the_node->north;
        break;

    case direction::EAST:
        return the_node->east;
        break;

    case direction::SOUTH:
        return the_node->south;
        break;

    case direction::WEST:
        return the_node->west;
        break;

    }

    return NULL;
}
