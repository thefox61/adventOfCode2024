#include "day5.h"
#include <unordered_set>

bool loadManualsAndRules(std::string input_file, std::unordered_map<int, std::vector<int>>& rules_map, std::vector<std::vector<int>>& manuals)
{
    std::ifstream the_file(input_file);

    std::string temp;


    while (the_file >> temp)
    {
        int split = temp.find_first_of("|");

        if (split == std::string::npos)
        {
            break;
        }

        int page = std::stoi(temp.substr(0, split));
        int restriction = std::stoi(temp.substr(split + 1, temp.length()));

        rules_map[page].emplace_back(restriction);
    }

    // load safety manuals
    bool end_file = false;

    while (!end_file)
    {
        std::vector<int> new_manual;

        std::stringstream ss(temp);
        std::string curr_page;

        while (getline(ss, curr_page, ','))
        {
            new_manual.emplace_back(std::stoi(curr_page));
        }

        manuals.emplace_back(new_manual);

        if (!(the_file >> temp))
        {
            end_file = true;
        }
    }

    return true;
}

bool validateManual(std::unordered_map<int, std::vector<int>>& rules, std::vector<int>& manual)
{
    std::unordered_set<int> seen_pages;

    for (int i = 0; i < manual.size(); i++)
    {
        for (int page : rules[manual[i]])
        {
            if (seen_pages.count(page) > 0)
            {
                return false;
            }
        }

        seen_pages.insert(manual[i]);
    }

    return true;
}

int countValidReports(std::unordered_map<int, std::vector<int>>& rules, std::vector<std::vector<int>>& manuals)
{
    int count = 0;

    for (int i = 0; i < manuals.size(); i++)
    {
        if (validateManual(rules, manuals[i]))
        {
            count++;
        }
    }

    return count;
}

int countMiddleValues(std::unordered_map<int, std::vector<int>>& rules, std::vector<std::vector<int>>& manuals)
{
    int count = 0;

    for (int i = 0; i < manuals.size(); i++)
    {
        if (validateManual(rules, manuals[i]))
        {
            int middle_index = (manuals[i].size() / 2);

            count += manuals[i][middle_index];
        }
    }

    return count;
}

int countMiddleValuesInvalid(std::unordered_map<int, std::vector<int>>& rules, std::vector<std::vector<int>>& manuals)
{
    int count = 0;

    for (int i = 0; i < manuals.size(); i++)
    {
        if (!validateManual(rules, manuals[i]))
        {
            bool corrected = false;
            while (!corrected)
            {
                if (!findAndSwapConflict(rules, manuals[i]))
                {
                    corrected = true;
                }
            }

            int middle_index = (manuals[i].size() / 2);

            count += manuals[i][middle_index];
        }
    }

    return count;
}

std::vector<std::pair<int, int>> findConflicts(std::unordered_map<int, std::vector<int>>& rules, std::vector<int>& manual)
{

    std::vector<std::pair<int, int>> conflicts;

    std::unordered_map<int, int> seen_pages_index;

    std::unordered_set<int> seen_pages;


    for (int i = 0; i < manual.size(); i++)
    {
        for (int page : rules[manual[i]])
        {
            if (seen_pages.count(page) > 0)
            {
                conflicts.emplace_back(manual[i], page);
            }
        }

        seen_pages.insert(manual[i]);

        seen_pages_index[manual[i]] = i;
    }

    return conflicts;
}

bool findAndSwapConflict(std::unordered_map<int, std::vector<int>>& rules, std::vector<int>& manual)
{
    //std::vector<std::pair<int, int>> conflicts;

    std::unordered_map<int, int> seen_pages_index;

    std::unordered_set<int> seen_pages;


    for (int i = 0; i < manual.size(); i++)
    {
        for (int page : rules[manual[i]])
        {
            if (seen_pages.count(page) > 0)
            {
                //conflicts.emplace_back(manual[i], page);
                
                int temp = manual[i];

                manual[i] = page;

                manual[seen_pages_index[page]] = temp;

                return true;
            }
        }

        seen_pages.insert(manual[i]);

        seen_pages_index[manual[i]] = i;
    }

    return false;
}


