#include "day14.h"

std::vector<robot> loadRobots(std::string input_file)
{
    std::ifstream the_file(input_file);

    std::string temp;

    std::vector<robot> robots;

    while (std::getline(the_file, temp))
    {
        robot curr_robot;

        int curr_pos_start = temp.find_first_of('=') + 1;
        int curr_pos_split = temp.find_first_of(',') + 1;
        int curr_pos_end = temp.find_first_of('v');

        curr_robot.start_pos.first = std::stoi(temp.substr(curr_pos_start, curr_pos_split - curr_pos_start));
        curr_robot.start_pos.second = std::stoi(temp.substr(curr_pos_split, curr_pos_end - curr_pos_split));


        int vel_start = temp.find_last_of('=') + 1;
        int vel_split = temp.find_last_of(',') + 1;

        curr_robot.velocity.first = std::stoi(temp.substr(vel_start, vel_split - vel_start));
        curr_robot.velocity.second = std::stoi(temp.substr(vel_split, temp.length() - vel_start));

        curr_robot.curr_pos = curr_robot.start_pos;

        robots.emplace_back(curr_robot);


    }

    return robots;
}

long long calculateSafetyFactor(std::vector<robot>& robots, int x_size, int y_size)
{
    int robot_quadrant = 0;

    std::vector<int> quadrant_counts(4, 0);

    for (int i = 0; i < robots.size(); i++)
    {
        robot_quadrant = determineQuadrant(robots[i], x_size, y_size);

        if (robot_quadrant != -1)
        {
            quadrant_counts[robot_quadrant]++;
        }
    }

    return quadrant_counts[0] * quadrant_counts[1] * quadrant_counts[2] * quadrant_counts[3];
}

int determineQuadrant(robot& robot, int x_size, int y_size)
{
    int middle_x = x_size / 2;
    int middle_y = y_size / 2;
    if (robot.curr_pos.first == middle_x || robot.curr_pos.second == middle_y)
    {
        return -1;
    }

    if (robot.curr_pos.first < middle_x && robot.curr_pos.second < middle_y)
    {
        return 0;
    }
    else if (robot.curr_pos.first > middle_x && robot.curr_pos.second < middle_y)
    {
        return 1;
    }
    else if (robot.curr_pos.first < middle_x && robot.curr_pos.second > middle_y)
    {
        return 2;
    }
    else if (robot.curr_pos.first > middle_x && robot.curr_pos.second > middle_y)
    {
        return 3;
    }

    return -1;
}

void updateRobotPosition(robot& the_robot, int seconds, int x_size, int y_size)
{
   /* long new_x = seconds * the_robot.velocity.first + the_robot.curr_pos.first;
    long new_y = seconds * the_robot.velocity.second + the_robot.curr_pos.second;

    new_x = std::abs(new_x) % x_size;
    new_y = std::abs(new_y) % y_size;

    the_robot.curr_pos.first = new_x;
    the_robot.curr_pos.second = new_y;*/

    for (int i = 0; i < seconds; i++)
    {
        the_robot.curr_pos.first += the_robot.velocity.first;
        if (the_robot.curr_pos.first < 0)
        {
            the_robot.curr_pos.first = the_robot.curr_pos.first + x_size;
        }
        if (the_robot.curr_pos.first >= x_size)
        {
            the_robot.curr_pos.first = the_robot.curr_pos.first - x_size;
        }

        the_robot.curr_pos.second += the_robot.velocity.second;

        if (the_robot.curr_pos.second < 0)
        {
            the_robot.curr_pos.second = the_robot.curr_pos.second + y_size;
        }
        if (the_robot.curr_pos.second >= y_size)
        {
            the_robot.curr_pos.second = the_robot.curr_pos.second - y_size;
        }
        
    }

}

void updateAllRobots(std::vector<robot>& robots, int seconds, int x_size, int y_size)
{
    for (int i = 0; i < robots.size(); i++)
    {
        updateRobotPosition(robots[i], seconds, x_size, y_size);
    }

}

void printRobotPositions(std::vector<robot>& robots, int x_size, int y_size)
{
    std::vector<std::vector<int>> map(y_size, std::vector<int>(x_size, 0));

    for (int i = 0; i < robots.size(); i++)
    {
        robot& curr_robot = robots[i];

        map[curr_robot.curr_pos.second][curr_robot.curr_pos.first]++;
    }

    for (int i = 0; i < map.size(); i++)
    {
        for (int j = 0; j < map[i].size(); j++)
        {
            std::cout << map[i][j];
        }
        std::cout << std::endl;
    }
}

bool hasOverlap(std::vector<robot>& robots, int x_size, int y_size)
{
    std::vector<std::vector<int>> map(y_size, std::vector<int>(x_size, 0));

    for (int i = 0; i < robots.size(); i++)
    {
        robot& curr_robot = robots[i];

        if (map[curr_robot.curr_pos.second][curr_robot.curr_pos.first] > 0)
        {
            return true;
        }

        map[curr_robot.curr_pos.second][curr_robot.curr_pos.first]++;
    }
    return false;
}

int findTreeSeconds(std::vector<robot>& robots, int x_size, int y_size)
{
    bool has_overlaps = true;

    long seconds = 0;
    while (has_overlaps)
    {
        updateAllRobots(robots, 1, x_size, y_size);

        has_overlaps = hasOverlap(robots, x_size, y_size);
        seconds++;
    }

    
    return seconds;
}
