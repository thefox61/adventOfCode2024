#include "day25.h"

locksAndKeys loadSchematics(std::string input_file)
{
    std::ifstream the_file(input_file);

    std::string temp;

    locksAndKeys result;

    while (std::getline(the_file, temp))
    {

        std::vector<std::string> temp_schematic(7, "");
       
        for (int i = 0; i < 7; i++)
        {
            temp_schematic[i] = temp;

            std::getline(the_file, temp);
        }

        if (temp_schematic[0][0] == '.')
        {
            result.keys.push_back(calculateKeyHeights(temp_schematic));
        }
        else if (temp_schematic[0][0] == '#')
        {
            result.locks.push_back(calculateLockHeights(temp_schematic));
        }


    }


    return result;
}

heights calculateLockHeights(std::vector<std::string>& schematic)
{
    heights lock;

    for (int i = 1; i < 7; i++)
    {
        if (schematic[i][0] == '#')
        {
            lock.height_0++;
        }
        if (schematic[i][1] == '#')
        {
            lock.height_1++;
        }
        if (schematic[i][2] == '#')
        {
            lock.height_2++;
        }
        if (schematic[i][3] == '#')
        {
            lock.height_3++;
        }
        if (schematic[i][4] == '#')
        {
            lock.height_4++;
        }

    }
    return lock;
}

heights calculateKeyHeights(std::vector<std::string>& schematic)
{
    heights key;

    for (int i = 5; i >= 0; i--)
    {
        if (schematic[i][0] == '#')
        {
            key.height_0++;
        }
        if (schematic[i][1] == '#')
        {
            key.height_1++;
        }
        if (schematic[i][2] == '#')
        {
            key.height_2++;
        }
        if (schematic[i][3] == '#')
        {
            key.height_3++;
        }
        if (schematic[i][4] == '#')
        {
            key.height_4++;
        }

    }
    return key;
}

bool checkFit(heights& lock, heights& key)
{
    if (lock.height_0 + key.height_0 > 5)
    {
        return false;
    }
    if (lock.height_1 + key.height_1 > 5)
    {
        return false;
    }
    if (lock.height_2 + key.height_2 > 5)
    {
        return false;
    }
    if (lock.height_3 + key.height_3 > 5)
    {
        return false;
    }
    if (lock.height_4 + key.height_4 > 5)
    {
        return false;
    }

    return true;
}

long long countPossiblePairs(locksAndKeys& locks_and_keys)
{
    long long count = 0;
    for (int i = 0; i < locks_and_keys.keys.size(); i++)
    {
        heights& curr_key = locks_and_keys.keys[i];

        for (int j = 0; j < locks_and_keys.locks.size(); j++)
        {
            if (checkFit(locks_and_keys.locks[j], curr_key))
            {
                count++;
            }
        }
    }


    return count;
}
