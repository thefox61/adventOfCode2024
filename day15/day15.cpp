#include "day15.h"
#include <set>

robotSimulation loadSimulation(std::string input_file)
{
    std::ifstream the_file(input_file);

    std::string temp;

    robotSimulation simulation;


    while (std::getline(the_file, temp))
    {
        if (temp.empty())
        {
            break;
        }

        std::vector<char> curr_row;

        for (int i = 0; i < temp.length(); i++)
        {
            curr_row.emplace_back(temp[i]);

            if (temp[i] == '@')
            {
                simulation.robot_position = std::pair<int, int>(simulation.map.size(), i);
            }
        }

        simulation.map.emplace_back(curr_row);
    }

    while (std::getline(the_file, temp))
    {
        for (int i = 0; i < temp.length(); i++)
        {
            simulation.moves.emplace_back(temp[i]);
        }
    }



    return simulation;
}

robotSimulation loadWideSimulation(std::string input_file)
{
    std::ifstream the_file(input_file);

    std::string temp;

    robotSimulation simulation;


    while (std::getline(the_file, temp))
    {
        if (temp.empty())
        {
            break;
        }

        std::vector<char> curr_row;

        for (int i = 0; i < temp.length(); i++)
        {
            

            if (temp[i] == '@')
            {
                simulation.robot_position = std::pair<int, int>(simulation.map.size(), curr_row.size());
                curr_row.emplace_back(temp[i]);
                curr_row.emplace_back('.');
            }
            else if (temp[i] == 'O')
            {
                curr_row.emplace_back('[');
                curr_row.emplace_back(']');
            }
            else
            {
                curr_row.emplace_back(temp[i]);
                curr_row.emplace_back(temp[i]);
            }
        }

        simulation.map.emplace_back(curr_row);
    }

    while (std::getline(the_file, temp))
    {
        for (int i = 0; i < temp.length(); i++)
        {
            simulation.moves.emplace_back(temp[i]);
        }
    }



    return simulation;
}

void simulate(robotSimulation& simulation, bool wide)
{
    std::vector<char>& moves = simulation.moves;
    for (int i = 0; i < moves.size(); i++)
    {
        simulateMove(simulation, moves[i], wide);
        
        
        /*printWarehouse(simulation);
        std::cout << std::endl;*/
    }
}

void simulateMove(robotSimulation& simulation, char move, bool wide)
{
    switch (move)
    {
    case '^':
        if (wide)
        {
            wideMoveUp(simulation);
        }
        else
        {
            moveUp(simulation);
        }
        
        break;
    case '>':
        moveRight(simulation);
        break;

    case '<':
        moveLeft(simulation);
        break;

    case'v':

        if (wide)
        {
            wideMoveDown(simulation);
        }
        else
        {
            moveDown(simulation);
        }
        
        break;

    }
}

void moveUp(robotSimulation& simulation)
{
    int x = simulation.robot_position.first - 1;
    int y = simulation.robot_position.second;

    while (simulation.map[x][y] != '.' && simulation.map[x][y] != '#')
    {
        x--;
    }

    if (simulation.map[x][y] == '#')
    {
        return;
    }

    int old_robot_x = simulation.robot_position.first;

    while (x != old_robot_x)
    {
        simulation.map[x][y] = simulation.map[x + 1][y];
        x++;
    }

    simulation.map[x][y] = '.';

    simulation.robot_position.first--;

}

void moveDown(robotSimulation& simulation)
{
    int x = simulation.robot_position.first + 1;
    int y = simulation.robot_position.second;

    while (simulation.map[x][y] != '.' && simulation.map[x][y] != '#')
    {
        x++;
    }

    if (simulation.map[x][y] == '#')
    {
        return;
    }

    int old_robot_x = simulation.robot_position.first;

    while (x != old_robot_x)
    {
        simulation.map[x][y] = simulation.map[x - 1][y];
        x--;
    }

    simulation.map[x][y] = '.';


    simulation.robot_position.first++;
}

void moveLeft(robotSimulation& simulation)
{
    int x = simulation.robot_position.first;
    int y = simulation.robot_position.second - 1;

    while (simulation.map[x][y] != '.' && simulation.map[x][y] != '#')
    {
        y--;
    }

    if (simulation.map[x][y] == '#')
    {
        return;
    }

    int old_robot_y = simulation.robot_position.second;


    while (y != old_robot_y)
    {
        simulation.map[x][y] = simulation.map[x][y + 1];
        y++;
    }

    simulation.map[x][y] = '.';

    simulation.robot_position.second--;
}

void moveRight(robotSimulation& simulation)
{
    int x = simulation.robot_position.first;
    int y = simulation.robot_position.second + 1;

    while (simulation.map[x][y] != '.' && simulation.map[x][y] != '#')
    {
        y++;
    }

    if (simulation.map[x][y] == '#')
    {
        return;
    }

    int old_robot_y = simulation.robot_position.second;

   
    while (y != old_robot_y)
    {
        simulation.map[x][y] = simulation.map[x][y - 1];
        y--;
    }

    simulation.map[x][y] = '.';

    simulation.robot_position.second++;
}

void printWarehouse(robotSimulation& simulation)
{
    for (int i = 0; i < simulation.map.size(); i++)
    {
        for (int j = 0; j < simulation.map[i].size(); j++)
        {
            std::cout << simulation.map[i][j];
        }

        std::cout << std::endl;
    }
}

long calculateGPSCoordinates(robotSimulation& simulation)
{
    long sum = 0;
    for (int i = 0; i < simulation.map.size(); i++)
    {
        for (int j = 0; j < simulation.map[i].size(); j++)
        {
            if (simulation.map[i][j] == 'O')
            {
                sum += i * 100 + j;
            }
        }
    }
    return sum;
}

long calculateGPSCoordinatesWide(robotSimulation& simulation)
{
    long sum = 0;
    for (int i = 0; i < simulation.map.size(); i++)
    {
        for (int j = 0; j < simulation.map[i].size(); j++)
        {
            if (simulation.map[i][j] == '[')
            {
                sum += i * 100 + j;
            }
        }
    }
    return sum;
}

void wideMoveUp(robotSimulation& simulation)
{
    std::vector<std::set<int>> boxes;

    int curr_x = simulation.robot_position.first - 1;


    bool clear_path = false;
    while (!clear_path)
    {
        clear_path = true;
        if (boxes.empty())
        {
            std::set<int> curr_row_boxes;
            if (simulation.map[curr_x][simulation.robot_position.second] == '.')
            {
                continue;
            }

            if (simulation.map[curr_x][simulation.robot_position.second] == '#')
            {
                return;
            }

            if (simulation.map[curr_x][simulation.robot_position.second] == '[')
            {
                curr_row_boxes.insert(simulation.robot_position.second);
            }

            if (simulation.map[curr_x][simulation.robot_position.second] == ']')
            {
                curr_row_boxes.insert(simulation.robot_position.second - 1);
            }

            boxes.emplace_back(curr_row_boxes);

            clear_path = false;
        }
        else
        {
            std::set<int>& last_row_boxes = boxes[boxes.size() - 1];

            std::set<int> curr_row_boxes;

            std::set<int>::iterator it = last_row_boxes.begin();

            while (it != last_row_boxes.end())
            {
                if (simulation.map[curr_x][*it] == '[')
                {
                    clear_path = false;
                    curr_row_boxes.insert(*it);
                }

                if (simulation.map[curr_x][*it] == ']')
                {
                    clear_path = false;
                    curr_row_boxes.insert(*it - 1);
                }

                if (simulation.map[curr_x][*it] == '#')
                {
                    clear_path = false;
                    return;
                }

                if (simulation.map[curr_x][*it + 1] == '[')
                {
                    clear_path = false;
                    curr_row_boxes.insert(*it + 1);
                }

                if (simulation.map[curr_x][*it + 1] == ']')
                {
                    clear_path = false;
                    curr_row_boxes.insert(*it);
                }

                if (simulation.map[curr_x][*it + 1] == '#')
                {
                    clear_path = false;
                    return;
                }
                it++;
            }

            if (!curr_row_boxes.empty())
            {
                boxes.emplace_back(curr_row_boxes);
            }
            
        }

        curr_x--;
    }

    curr_x++;

    for (int i = boxes.size() - 1; i >= 0; i--)
    {
        std::set<int>::iterator it = boxes[i].begin();

        while (it != boxes[i].end())
        {
            simulation.map[curr_x][*it] = '[';
            simulation.map[curr_x][*it + 1] = ']';

            simulation.map[curr_x + 1][*it] = '.';
            simulation.map[curr_x + 1][*it + 1] = '.';


            it++;
        }
        curr_x++;
    }

    simulation.map[simulation.robot_position.first][simulation.robot_position.second] = '.';
    simulation.map[simulation.robot_position.first - 1][simulation.robot_position.second] = '@';


    simulation.robot_position.first--;
}

void wideMoveDown(robotSimulation& simulation)
{
    std::vector<std::set<int>> boxes;

    int curr_x = simulation.robot_position.first + 1;


    bool clear_path = false;
    while (!clear_path)
    {
        clear_path = true;
        if (boxes.empty())
        {
            std::set<int> curr_row_boxes;
            if (simulation.map[curr_x][simulation.robot_position.second] == '.')
            {
                continue;
            }

            if (simulation.map[curr_x][simulation.robot_position.second] == '#')
            {
                return;
            }

            if (simulation.map[curr_x][simulation.robot_position.second] == '[')
            {
                curr_row_boxes.insert(simulation.robot_position.second);
            }

            if (simulation.map[curr_x][simulation.robot_position.second] == ']')
            {
                curr_row_boxes.insert(simulation.robot_position.second - 1);
            }

            boxes.emplace_back(curr_row_boxes);
            clear_path = false;
        }
        else
        {
            std::set<int>& last_row_boxes = boxes[boxes.size() - 1];

            std::set<int> curr_row_boxes;

            std::set<int>::iterator it = last_row_boxes.begin();

            while (it != last_row_boxes.end())
            {
                if (simulation.map[curr_x][*it] == '[')
                {
                    clear_path = false;
                    curr_row_boxes.insert(*it);
                }

                if (simulation.map[curr_x][*it] == ']')
                {
                    clear_path = false;
                    curr_row_boxes.insert(*it - 1);
                }

                if (simulation.map[curr_x][*it] == '#')
                {
                    clear_path = false;
                    return;
                }

                if (simulation.map[curr_x][*it + 1] == '[')
                {
                    clear_path = false;
                    curr_row_boxes.insert(*it + 1);
                }

                if (simulation.map[curr_x][*it + 1] == ']')
                {
                    clear_path = false;
                    curr_row_boxes.insert(*it);
                }

                if (simulation.map[curr_x][*it + 1] == '#')
                {
                    clear_path = false;
                    return;
                }
                it++;
            }

            if (!curr_row_boxes.empty())
            {
                boxes.emplace_back(curr_row_boxes);
            }
        }

        curr_x++;
    }

    curr_x--;

    for (int i = boxes.size() - 1; i >= 0; i--)
    {
        std::set<int>::iterator it = boxes[i].begin();

        while (it != boxes[i].end())
        {
            simulation.map[curr_x][*it] = '[';
            simulation.map[curr_x][*it + 1] = ']';

            simulation.map[curr_x - 1][*it] = '.';
            simulation.map[curr_x - 1][*it + 1] = '.';


            it++;
        }
        curr_x--;
    }

    simulation.map[simulation.robot_position.first][simulation.robot_position.second] = '.';
    simulation.map[simulation.robot_position.first + 1][simulation.robot_position.second] = '@';

    simulation.robot_position.first++;

}


