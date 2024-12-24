#include "day21.h"
#include <queue>

std::map<char, std::pair<int, int>> numpad;
std::map<char, std::pair<int, int>> directionpad;


std::map<unsigned long long, unsigned long long>  robot_costs;

int num_robots = 25;

void loadPositionMaps()
{
    std::vector<std::vector<char>> numpad_layout = { {'7', '8', '9'}, {'4', '5', '6'}, {'1', '2', '3'}, {'X', '0', 'A'} };
    std::vector<std::vector<char>> directionpad_layout = { {'X', '^', 'A'},  {'<', 'v', '>'} };

    for (int i = 0; i < numpad_layout.size(); i++)
    {
        for (int j = 0; j < numpad_layout[i].size(); j++)
        {
            numpad[numpad_layout[i][j]] = std::make_pair(i, j);
        }
    }

    for (int i = 0; i < directionpad_layout.size(); i++)
    {
        for (int j = 0; j < directionpad_layout[i].size(); j++)
        {
            directionpad[directionpad_layout[i][j]] = std::make_pair(i, j);
        }
    }

}

unsigned long long calculateComplexetiesSum(std::string input_file)
{
    unsigned long long sum = 0;

    std::ifstream the_file(input_file);

    std::string temp;

    while (std::getline(the_file, temp))
    {
        sum += calculateComplexity(temp);
    }

    return sum;
}

unsigned long long hashCost(int i0, int j0, int i1, int j1, int robot_num)
{
    unsigned long long hash = i0;

    hash = hash << 4;

    hash += j0;

    hash = hash << 4;

    hash += i1;

    hash = hash << 4;
    
    hash += j1;

    hash = hash << 30;

    hash += robot_num;


    return hash;
}

unsigned long long calculateLowestCost(int i0, int j0, int i1, int j1)
{
    std::deque<pathState> queue;

    unsigned long long result = ULLONG_MAX;

    queue.push_back(pathState(i0, j0, ""));

    while (!queue.empty())
    {
        pathState currState = queue.front();
        queue.pop_front();

        if (currState.i == i1 && currState.j == j1)
        {
            //calc the cheapest robot inputs
            unsigned long long curr = calculateRobotCost(currState.inputs + 'A', num_robots);
            // compare to current value
            result = std::min(result, curr);
            continue;
        }

        // can't go on empty space
        if (currState.i == 3 && currState.j == 0)
        {
            continue;
        }


        if (currState.i < i1)
        {
            queue.push_back(pathState(currState.i + 1, currState.j, currState.inputs + 'v'));
        }
        else if (currState.i > i1)
        {
            queue.push_back(pathState(currState.i - 1, currState.j, currState.inputs + '^'));
        }

        if (currState.j < j1)
        {
            queue.push_back(pathState(currState.i, currState.j + 1, currState.inputs + '>'));
        }
        else if (currState.j > j1)
        {
            queue.push_back(pathState(currState.i, currState.j - 1, currState.inputs + '<'));
        }
    }

    return result;
}

unsigned long long calculateRobotCost(std::string input, int robot_num)
{
    if (robot_num == 0)
    {
        return input.length();
    }

    char curr_char = 'A';
    std::pair<int, int> curr_pos = directionpad[curr_char];

    unsigned long long result = 0;

    for (int i = 0; i < input.length(); i++)
    {
        std::pair<int, int> next_pos = directionpad[input[i]];
        result += calculateLowestDirectionPad(curr_pos.first, curr_pos.second, next_pos.first, next_pos.second, robot_num);

        curr_char = input[i];
        curr_pos = next_pos;
    }

    return result;
}

unsigned long long calculateLowestDirectionPad(int i0, int j0, int i1, int j1, int robot_num)
{
    unsigned long long hash = hashCost(i0, j0, i1, j1, robot_num);
    std::map<unsigned long long, unsigned long long>::iterator it = robot_costs.find(hash);

    if (it != robot_costs.end())
    {
        return robot_costs[hash];
    }


    std::deque<pathState> queue;

    queue.push_back(pathState(i0, j0, ""));

    unsigned long long result = ULLONG_MAX;

    while (!queue.empty())
    {
        pathState currState = queue.front();
        queue.pop_front();

        if (currState.i == i1 && currState.j == j1)
        {
            // calc the cheapest robot inputs
            unsigned long long curr = calculateRobotCost(currState.inputs + 'A', robot_num - 1);
            // compare to current value
            result = std::min(result, curr);

            continue;
        }

        // can't go on empty space
        if (currState.i == 0 && currState.j == 0)
        {
            continue;
        }

        if (currState.i < i1)
        {
            queue.push_back(pathState(currState.i + 1, currState.j, currState.inputs + 'v'));
        }
        else if (currState.i > i1)
        {
            queue.push_back(pathState(currState.i - 1, currState.j, currState.inputs + '^'));
        }

        if (currState.j < j1)
        {
            queue.push_back(pathState(currState.i, currState.j + 1, currState.inputs + '>'));
        }
        else if (currState.j > j1)
        {
            queue.push_back(pathState(currState.i, currState.j - 1, currState.inputs + '<'));
        }
    }
    robot_costs[hash] = result;
    return result;
}

unsigned long long calculateComplexity(std::string code)
{
    unsigned long long result = 0;

    char curr_char = 'A';
    std::pair<int, int> curr_pos = numpad[curr_char];


    for (int i = 0; i < code.length(); i++)
    {
        std::pair<int, int> next_pos = numpad[code[i]];

        result += calculateLowestCost(curr_pos.first, curr_pos.second, next_pos.first, next_pos.second);

        curr_char = code[i];
        curr_pos = numpad[curr_char];
    }

    if (result < 0)
    {
        bool breakpoint = false;
    }

    int code_value = std::stoi(code.substr(0, 3));

    result *= code_value;

    return result;
}



