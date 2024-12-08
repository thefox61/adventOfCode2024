#include "day8.h"

std::unordered_map<char, std::vector<std::pair<int, int>>> getAntennaFrequencies(std::vector<std::vector<char>>& map)
{
    std::unordered_map<char, std::vector<std::pair<int, int>>> frequencies_map;
    for (int i = 0; i < map.size(); i++)
    {
        for (int j = 0; j < map[i].size(); j++)
        {
            if (map[i][j] != '.')
            {
                frequencies_map[map[i][j]].emplace_back(i, j);
            }
        }
    }


    return frequencies_map;
}

int countAntinodes(std::vector<std::vector<char>>& map)
{
    int count = 0;

    std::unordered_map<char, std::vector<std::pair<int, int>>> frequencies_map = getAntennaFrequencies(map);

    std::vector<std::vector<char>> antinodes_map(map.size(), std::vector<char>(map[0].size(), '.'));

    std::unordered_map<char, std::vector<std::pair<int, int>>>::iterator it = frequencies_map.begin();

    while (it != frequencies_map.end())
    {

        std::vector<std::pair<int, int>>& curr_frequency = it->second;
        for (int i = 0; i < curr_frequency.size(); i++)
        {
            for (int j = i + 1; j < curr_frequency.size(); j++)
            {
                int delta_i = curr_frequency[i].first - curr_frequency[j].first;
                int delta_j = curr_frequency[i].second - curr_frequency[j].second;

                int upper_i = curr_frequency[i].first + delta_i;
                int upper_j = curr_frequency[i].second + delta_j;
                // check upper
                char upper = getAntennaMapIndex(upper_i, upper_j, map);

                if (upper != '$')
                {
                    if (antinodes_map[upper_i][upper_j] == '.')
                    {
                        antinodes_map[upper_i][upper_j] = '#';
                        count++;
                    }
                }

                // check lower
                int lower_i = curr_frequency[j].first - delta_i;
                int lower_j = curr_frequency[j].second - delta_j;

                char lower = getAntennaMapIndex(lower_i, lower_j, map);
                


                if (lower != '$')
                {
                    if (antinodes_map[lower_i][lower_j] == '.')
                    {
                        antinodes_map[lower_i][lower_j] = '#';
                        count++;
                    }
                }
            }
        }

        it++;
    }
   

    return count;
}

int countAntinodesTwo(std::vector<std::vector<char>>& map)
{
    int count = 0;

    std::unordered_map<char, std::vector<std::pair<int, int>>> frequencies_map = getAntennaFrequencies(map);

    std::vector<std::vector<char>> antinodes_map(map.size(), std::vector<char>(map[0].size(), '.'));

    std::unordered_map<char, std::vector<std::pair<int, int>>>::iterator it = frequencies_map.begin();

    while (it != frequencies_map.end())
    {

        std::vector<std::pair<int, int>>& curr_frequency = it->second;
        for (int i = 0; i < curr_frequency.size(); i++)
        {
            for (int j = i + 1; j < curr_frequency.size(); j++)
            {
                int delta_i = curr_frequency[i].first - curr_frequency[j].first;
                int delta_j = curr_frequency[i].second - curr_frequency[j].second;

                int upper_i = curr_frequency[i].first + delta_i;
                int upper_j = curr_frequency[i].second + delta_j;
                // check upper
                char upper = getAntennaMapIndex(upper_i, upper_j, map);

                while (upper != '$')
                {
                    if (antinodes_map[upper_i][upper_j] == '.')
                    {
                        antinodes_map[upper_i][upper_j] = '#';
                        count++;
                    }

                    upper_i += delta_i;
                    upper_j += delta_j;

                    upper = getAntennaMapIndex(upper_i, upper_j, map);
                }


                // check lower
                int lower_i = curr_frequency[j].first - delta_i;
                int lower_j = curr_frequency[j].second - delta_j;

                char lower = getAntennaMapIndex(lower_i, lower_j, map);


                while (lower != '$')
                {
                    if (antinodes_map[lower_i][lower_j] == '.')
                    {
                        antinodes_map[lower_i][lower_j] = '#';
                        count++;
                    }

                    lower_i -= delta_i;
                    lower_j -= delta_j;

                    lower = getAntennaMapIndex(lower_i, lower_j, map);
                }

                if (antinodes_map[curr_frequency[j].first][curr_frequency[j].second] != '#')
                {
                    antinodes_map[curr_frequency[j].first][curr_frequency[j].second] = '#';
                    count++;
                }

            }


            if (antinodes_map[curr_frequency[i].first][curr_frequency[i].second] != '#')
            {
                antinodes_map[curr_frequency[i].first][curr_frequency[i].second] = '#';
                count++;
            }
        }

        it++;
    }


    return count;
}

char getAntennaMapIndex(int i, int j, std::vector<std::vector<char>>& map)
{
    if (i >= map.size() || j >= map[i].size())
    {
        return '$';
    }

    return map[i][j];
}
