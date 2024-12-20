#include "day19.h"

onsenTowels loadOnsenTowels(std::string input_file)
{
    std::ifstream the_file(input_file);

    std::string temp;

    onsenTowels the_towels;

    std::getline(the_file, temp);

    int comma_loc = temp.find_first_of(',');
    while (comma_loc < temp.length())
    {
        the_towels.towel_colours.emplace_back(temp.substr(0, comma_loc));

        temp = temp.substr(comma_loc + 2, temp.length() - comma_loc);

        comma_loc = temp.find_first_of(',');
    }

    the_towels.towel_colours.emplace_back(temp);

    std::getline(the_file, temp);
    while (std::getline(the_file, temp))
    {
        the_towels.desired_patterns.emplace_back(temp);
    }


    return the_towels;
}

bool canBuildPattern(std::string desired_pattern, std::set<std::string>& colours_set)
{
    if (desired_pattern.empty())
    {
        return true;
    }


    for (int i = 1; i <= desired_pattern.length(); i++)
    {
        std::string sub_pattern = desired_pattern.substr(0, i);
        if (colours_set.count(sub_pattern) > 0)
        {
            if (canBuildPattern(desired_pattern.substr(i , desired_pattern.length() - i), colours_set))
            {
                return true;
            }
        }
    }

    return false;
}

long countValidPatterns(onsenTowels& the_towels)
{
    std::set<std::string> colours_set(the_towels.towel_colours.begin(), the_towels.towel_colours.end());

    long count = 0;
    for (int i = 0; i < the_towels.desired_patterns.size(); i++)
    {
        if (canBuildPattern(the_towels.desired_patterns[i], colours_set))
        {
            count++;
        }
    }
    return count;
}

long long countPatternOptions(onsenTowels& the_towels)
{
    std::set<std::string> colours_set(the_towels.towel_colours.begin(), the_towels.towel_colours.end());


    long long count = 0;
    for (int i = 0; i < the_towels.desired_patterns.size(); i++)
    {
        std::map<std::string, long long> saved_counts;
        count += possiblePatternOptions(the_towels.desired_patterns[i], colours_set, saved_counts);
    }

    return count;
}

long long possiblePatternOptions(std::string desired_pattern, std::set<std::string>& colours_set, std::map<std::string, long long>& saved_counts)
{
    if (desired_pattern.empty())
    {
        return 1;
    }

    long long count = 0;
    for (int i = 1; i <= desired_pattern.length(); i++)
    {
        std::string sub_pattern = desired_pattern.substr(0, i);
        if (colours_set.count(sub_pattern) > 0)
        {
            std::string remaining_pattern = desired_pattern.substr(i, desired_pattern.length() - i);
            if (saved_counts.count(remaining_pattern) == 0)
            {
                saved_counts[remaining_pattern] = possiblePatternOptions(remaining_pattern, colours_set, saved_counts);
            }
            
            count += saved_counts[remaining_pattern];
        }
    }

    return count;
}
