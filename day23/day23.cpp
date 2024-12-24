#include "day23.h"
#include <algorithm>


computerGraph loadComputerGraph(std::string input_file)
{
    computerGraph computer_graph;

    computer_graph.computers.reserve(676);

    std::ifstream the_file(input_file);

    std::string temp;

    unsigned long curr_id = 0;

    while (std::getline(the_file, temp))
    {
        std::string comp_1 = temp.substr(0, 2);

        std::string comp_2 = temp.substr(3, 2);


        if (computer_graph.computer_map.count(comp_1) == 0)
        {
            computer_graph.computers.emplace_back(curr_id, comp_1);
            curr_id++;

            computer_graph.computer_map[comp_1] = &computer_graph.computers[computer_graph.computers.size() - 1];
        }

        if (computer_graph.computer_map.count(comp_2) == 0)
        {
            computer_graph.computers.emplace_back(curr_id, comp_2);
            curr_id++;

            computer_graph.computer_map[comp_2] = &computer_graph.computers[computer_graph.computers.size() - 1];
        }

        computer_graph.computer_map[comp_1]->connections.insert(comp_2);

        computer_graph.computer_map[comp_2]->connections.insert(comp_1);
    }


    return computer_graph;
}

long long findConnectedSetsT(computerGraph& computer_graph)
{
    std::set<std::vector<std::string>> connected_sets;

    std::map<std::string, bool> visited;


    for (int i = 0; i < computer_graph.computers.size(); i++)
    {

        computer* curr_computer = &computer_graph.computers[i];

        if (visited[curr_computer->name] || curr_computer->name.find_first_of('t') == std::string::npos || curr_computer->name.find_first_of('t') != 0)
        {
            continue;
        }

        visited[curr_computer->name] = true;

        if (curr_computer->connections.size() < 2)
        {
            continue;
        }

        std::set<std::string>::iterator it = curr_computer->connections.begin();

        while (it != curr_computer->connections.end())
        { 

            std::set<std::string> computer_intersection;

            computer* curr_connection = computer_graph.computer_map[*it];

            std::set_intersection(curr_computer->connections.begin(), curr_computer->connections.end(), curr_connection->connections.begin(),
                curr_connection->connections.end(), std::inserter(computer_intersection, computer_intersection.begin()));

            std::set<std::string>::iterator intersection_it = computer_intersection.begin();

            while (intersection_it != computer_intersection.end())
            {
                std::vector<std::string> intersection = { curr_computer->name, curr_connection->name, *intersection_it };

                std::sort(intersection.begin(), intersection.end());

                connected_sets.insert(intersection);

                intersection_it++;
            }

            it++;
        }
     

        


    }

    return connected_sets.size();
}

std::vector<std::string> findLargestConnectedSet(computerGraph& computer_graph)
{

    std::vector<std::string> largestSet;

    for (int i = 0; i < computer_graph.computers.size(); i++)
    {
        computer* curr_computer = &computer_graph.computers[i];
        std::set<std::string>::iterator it = curr_computer->connections.begin();

        while (it != curr_computer->connections.end())
        {
            std::vector<std::string> curr_set = { curr_computer->name, *it};

            std::set<std::string> computer_intersection;

            computer* curr_connection = computer_graph.computer_map[*it];

            std::set_intersection(curr_computer->connections.begin(), curr_computer->connections.end(), curr_connection->connections.begin(),
                curr_connection->connections.end(), std::inserter(computer_intersection, computer_intersection.begin()));

            std::set<std::string>::iterator intersection_it = computer_intersection.begin();

            while (intersection_it != computer_intersection.end())
            {
                bool connected = true;
                for (std::string c : curr_set)
                {
                    if (computer_graph.computer_map[*intersection_it]->connections.count(c) == 0)
                    {
                        connected = false;
                        break;
                    }
                }

                if (connected)
                {
                    curr_set.emplace_back(*intersection_it);
                }
                
                intersection_it++;
            }

            if (curr_set.size() > largestSet.size())
            {
                largestSet = curr_set;
            }

            it++;

        }

    }

    std::sort(largestSet.begin(), largestSet.end());

    return largestSet;
}
