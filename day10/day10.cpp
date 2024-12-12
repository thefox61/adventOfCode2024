#include "day10.h"

std::vector<std::vector<int>> loadTopoMap(std::string input_file)
{
    std::ifstream the_file(input_file);

    std::string temp;

    std::vector<std::vector<int>> topo_map;

    while (std::getline(the_file, temp))
    {
        std::vector<int> curr_row;
        for (int i = 0; i < temp.length(); i++)
        {
            curr_row.emplace_back(temp[i] - '0');
        }
        topo_map.push_back(curr_row);
    }

    return topo_map;
}

int getIndexValue(int i, int j, std::vector<std::vector<int>>& topo_map)
{
    if (i >= topo_map.size() || i < 0 || j >= topo_map[i].size() || j < 0)
    {
        return -1;
    }
    return topo_map[i][j];
}

int countTrails(std::vector<std::vector<int>>& topo_map)
{
    int count = 0;
    for (int i = 0; i < topo_map.size(); i++)
    {
        for (int j = 0; j < topo_map[i].size(); j++)
        {
            if (getIndexValue(i, j, topo_map) == 0)
            {
                std::vector<std::pair<int, int>> visited_nines;
                count += countTrail(i, j, topo_map, &visited_nines);
            }
        }
    }
    return count;
}

int countTrail(int i, int j, std::vector<std::vector<int>>& topo_map, std::vector<std::pair<int, int>>* visited_nines)
{
    int value = getIndexValue(i, j, topo_map);

    if (value == -1)
    {
        return 0;
    }
    else if (value == 9)
    {
        std::pair<int, int> this_nine(i, j);

        for (int i = 0; i < visited_nines->size(); i++)
        {
            
           /* if ((*visited_nines)[i] == this_nine)
            {
                return 0;
            }*/

            
        }

        //(*visited_nines).emplace_back(i, j);
        return 1;
    }

    int next_value = value + 1;
    int result = 0;

    if (getIndexValue(i + 1, j, topo_map) == next_value)
    {
        result += countTrail(i + 1, j, topo_map, visited_nines);
    }

    if (getIndexValue(i - 1, j, topo_map) == next_value)
    {
        result += countTrail(i - 1, j, topo_map, visited_nines);
    }

    if (getIndexValue(i , j + 1, topo_map) == next_value)
    {
        result += countTrail(i, j + 1, topo_map, visited_nines);
    }

    if (getIndexValue(i, j - 1, topo_map) == next_value)
    {
        result += countTrail(i, j - 1, topo_map, visited_nines);
    }

    return result;
}


