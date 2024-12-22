#include "day20.h"
#include <queue>

graph loadGraph(std::string input_file)
{
    std::ifstream the_file(input_file);

    std::string temp;

    graph the_graph;

    int id_count = 0;
    while (std::getline(the_file, temp))
    {
        std::vector<node> curr_row;
        for (int i = 0; i < temp.length(); i++)
        {
            curr_row.emplace_back(temp[i], id_count);
            id_count++;
        }

        the_graph.nodes.emplace_back(curr_row);
    }

    for (int i = 0; i < the_graph.nodes.size(); i++)
    {
        for (int j = 0; j < the_graph.nodes[i].size(); j++)
        {
            if (the_graph.nodes[i][j].value == 'S')
            {
                the_graph.start_node = &the_graph.nodes[i][j];
            }
            else if (the_graph.nodes[i][j].value == 'E')
            {
                the_graph.end_node = &the_graph.nodes[i][j];
            }

            the_graph.nodes[i][j].north = getGraphNode(the_graph.nodes, i - 1, j, true);
            the_graph.nodes[i][j].east = getGraphNode(the_graph.nodes, i, j + 1, true);
            the_graph.nodes[i][j].south = getGraphNode(the_graph.nodes, i + 1, j, true);
            the_graph.nodes[i][j].west = getGraphNode(the_graph.nodes, i, j - 1, true);

            the_graph.id_to_node[the_graph.nodes[i][j].id] = &the_graph.nodes[i][j];

            the_graph.nodes[i][j].position = std::make_pair(i, j);
        }
    }


    return the_graph;
}

node* getGraphNode(std::vector<std::vector<node>>& graph, int i, int j, bool return_walls)
{
    if (i < 0 || i >= graph.size() || j < 0 || j >= graph[i].size())
    {
        return NULL;
    }

    if (graph[i][j].value == '#' && !return_walls)
    {
        return NULL;
    }

    return &graph[i][j];
}

long countNumCheats(graph& the_graph)
{
    long num_cheats = 0;


    return 0;
}

long long findShortestPathLength(graph& the_graph, std::vector<int>& final_path)
{
    std::map<std::pair<int, direction>, long> lowest_cost;

    std::priority_queue<pathState, std::vector<pathState>, std::greater<pathState>> queue;

    std::map<std::pair<int, direction>, std::vector<int>> paths;

    

    if (the_graph.start_node->north && the_graph.start_node->north->value != '#')
    {
        queue.push(pathState(0, the_graph.start_node, direction::NORTH));
    }
    if (the_graph.start_node->east && the_graph.start_node->east->value != '#')
    {
        queue.push(pathState(0, the_graph.start_node, direction::EAST));
    }
    if (the_graph.start_node->south && the_graph.start_node->south->value != '#')
    {
        queue.push(pathState(0, the_graph.start_node, direction::SOUTH));
    }
    if (the_graph.start_node->west && the_graph.start_node->west->value != '#')
    {
        queue.push(pathState(0, the_graph.start_node, direction::WEST));
    }


    while (!queue.empty())
    {
        pathState curr_state = queue.top();
        queue.pop();

        std::pair<int, direction> curr_pair = std::make_pair(curr_state.state_node->id, curr_state.state_direction);

        std::set<int> path = curr_state.path;
        std::vector<int> ordered_path = curr_state.ordered_path;

        if (path.count(curr_state.state_node->id) == 0)
        {
            path.insert(curr_state.state_node->id);
            ordered_path.emplace_back(curr_state.state_node->id);
        }


        if (lowest_cost.count(curr_pair)
            && curr_state.cost >= lowest_cost[curr_pair])
        {
            continue;
        }

        lowest_cost[curr_pair] = curr_state.cost;
        
        paths[curr_pair] = ordered_path;

        if (curr_state.state_node->north && curr_state.state_node->north->value != '#')
        {
            queue.push(pathState(curr_state.cost + 1, curr_state.state_node->north, direction::NORTH, path, ordered_path));
        }
        if (curr_state.state_node->east && curr_state.state_node->east->value != '#')
        {
            queue.push(pathState(curr_state.cost + 1, curr_state.state_node->east, direction::EAST, path, ordered_path));
        }
        if (curr_state.state_node->south && curr_state.state_node->south->value != '#')
        {
            queue.push(pathState(curr_state.cost + 1, curr_state.state_node->south, direction::SOUTH, path, ordered_path));
        }
        if (curr_state.state_node->west && curr_state.state_node->west->value != '#')
        {
            queue.push(pathState(curr_state.cost + 1, curr_state.state_node->west, direction::WEST, path, ordered_path));
        }

    }
    long end_cost = LONG_MAX;

    node* goal_node = the_graph.end_node;

    if (lowest_cost.count(std::make_pair(goal_node->id, direction::NORTH)) > 0)
    {
        end_cost = std::min(end_cost, lowest_cost[std::make_pair(goal_node->id, direction::NORTH)]);
        final_path = paths[std::make_pair(goal_node->id, direction::NORTH)];
    }
    if (lowest_cost.count(std::make_pair(goal_node->id, direction::EAST)) > 0)
    {
        end_cost = std::min(end_cost, lowest_cost[std::make_pair(goal_node->id, direction::EAST)]);
        final_path = paths[std::make_pair(goal_node->id, direction::EAST)];
    }
    if (lowest_cost.count(std::make_pair(goal_node->id, direction::SOUTH)) > 0)
    {
        end_cost = std::min(end_cost, lowest_cost[std::make_pair(goal_node->id, direction::SOUTH)]);
        final_path = paths[std::make_pair(goal_node->id, direction::SOUTH)];
    }
    if (lowest_cost.count(std::make_pair(goal_node->id, direction::WEST)) > 0)
    {
        end_cost = std::min(end_cost, lowest_cost[std::make_pair(goal_node->id, direction::WEST)]);
        final_path = paths[std::make_pair(goal_node->id, direction::WEST)];
    }

    // store path indexes
    the_graph.start_node->path_index = 0;
    for (int i = 0; i < final_path.size(); i++)
    {
        the_graph.id_to_node[final_path[i]]->path_index = i + 1;
    }

    return end_cost;
}

long checkCheat(node* path_node, node* cheat_node, direction node_direction)
{
    node* next_node = NULL;
    switch (node_direction)
    {
    case direction::NORTH:
        next_node = cheat_node->north;
        break;
    case direction::EAST:
        next_node = cheat_node->east;
        break;
    case direction::WEST:
        next_node = cheat_node->west;
        break;
    case direction::SOUTH:
        next_node = cheat_node->south;
        break;
    }

    if(next_node && next_node->value != '#' && next_node != path_node)
    { 
        return next_node->path_index - path_node->path_index;
    }

    return -1;
}

long long checkAllCheats(graph& the_graph, std::vector<int>& final_path, long threshold)
{
    node* curr_node = the_graph.start_node;

    std::set<int> checked_nodes;
    
    long long cheat_count = 0;
    for (int i = 0; i < final_path.size(); i++)
    {
        node* curr_node = the_graph.id_to_node[final_path[i]];

        if (curr_node->north && curr_node->north->value == '#' && checked_nodes.count(curr_node->north->id) == 0)
        {
            cheat_count += checkNodeCheats(curr_node, curr_node->north, threshold);
            checked_nodes.insert(curr_node->north->id);
        }

        if (curr_node->east && curr_node->east->value == '#' && checked_nodes.count(curr_node->east->id) == 0)
        {
            cheat_count += checkNodeCheats(curr_node, curr_node->east, threshold);
            checked_nodes.insert(curr_node->east->id);
        }

        if (curr_node->south && curr_node->south->value == '#' && checked_nodes.count(curr_node->south->id) == 0)
        {
            cheat_count += checkNodeCheats(curr_node, curr_node->south, threshold);
            checked_nodes.insert(curr_node->south->id);
        }

        if (curr_node->west && curr_node->west->value == '#' && checked_nodes.count(curr_node->west->id) == 0)
        {
            cheat_count += checkNodeCheats(curr_node, curr_node->west, threshold);
            checked_nodes.insert(curr_node->west->id);
        }
    }


    return cheat_count;
}

long long checkAllCheatsPart2(graph& the_graph, std::vector<int>& final_path, long threshold)
{
    long long count = 0;
    for (int i = 0; i < final_path.size(); i++)
    {
        node* node1 = the_graph.id_to_node[final_path[i]];
        for (int j = i + 1; j < final_path.size(); j++)
        {
            node* node2 = the_graph.id_to_node[final_path[j]];

            long distance = calculateDistance(node1, node2);

            if(distance <= 20)
            {
                if ((node2->path_index - node1->path_index - distance) >= threshold)
                {
                    count++;
                }
                
            }

        }
    }

    return count;
}

int checkNodeCheats(node* path_node, node* cheat_node, long threshold)
{
    int cheat_count = 0;

    if (checkCheat(path_node, cheat_node, direction::NORTH) >= threshold)
    {
        cheat_count++;
    }
    if (checkCheat(path_node, cheat_node, direction::EAST) >= threshold)
    {
        cheat_count++;
    }
    if (checkCheat(path_node, cheat_node, direction::SOUTH) >= threshold)
    {
        cheat_count++;
    }
    if (checkCheat(path_node, cheat_node, direction::WEST) >= threshold)
    {
        cheat_count++;
    }

    return cheat_count;
}

long calculateDistance(node* node1, node* node2)
{
    long distance = std::abs(node2->position.first - node1->position.first) + std::abs(node2->position.second - node1->position.second);

    return distance;
}
