#include "day22.h"

unsigned long long getNextSecretNum(unsigned long long secret_num)
{
    unsigned long long temp = secret_num * 64;

    secret_num = secret_num ^ temp;
    secret_num = secret_num % 16777216;

    temp = secret_num / 32;

    secret_num = secret_num ^ temp;
    secret_num = secret_num % 16777216;


    temp = secret_num * 2048;

    secret_num = secret_num ^ temp;
    secret_num = secret_num % 16777216;

    return secret_num;
}

unsigned long long calcNthSecretNum(unsigned long long secret_num, int n)
{
    for (int i = 0; i < n; i++)
    {
        secret_num = getNextSecretNum(secret_num);
    }

    return secret_num;
}

unsigned long long getSecretNumSum(std::string input_file)
{
    unsigned long long sum = 0;

    std::ifstream the_file(input_file);

    std::string temp;

    unsigned long long curr;

    while (std::getline(the_file, temp))
    {
        curr = std::stoull(temp);
        sum += calcNthSecretNum(curr, 2000);
    }

    
    return sum;
}

std::vector<int> findBestSequence(std::string input_file, long long& most_bananas)
{
    std::map<std::vector<int>, int > sequences;


    std::vector<int> result;
    int max = 0;

    std::ifstream the_file(input_file);

    std::string temp;

    unsigned long long curr;

   

    while (std::getline(the_file, temp))
    {
        curr = std::stoull(temp);
        getSequences(curr, 2000, sequences);
    }

    std::map<std::vector<int>, int >::iterator it = sequences.begin();

    while (it != sequences.end())
    {
        if (it->second > max)
        {
            max = it->second;
            result = it->first;
        }


        it++;

    }

    most_bananas = max;

    return result;
}

void getSequences(unsigned long long secret_num, int n, std::map<std::vector<int>, int>& sequences)
{
    int last = secret_num % 10;
    int curr;

    std::vector<int> values(n, 0);

    std::vector<int> curr_sequence(4, 0);

    std::map<std::vector<int>, bool> seen;

    int start = 0;

    for (int i = 0; i < n; i++)
    {
        secret_num = getNextSecretNum(secret_num);
        curr = secret_num % 10;

        values[i] = curr - last;

        last = curr;

        if (i - start == 3)
        {
            for (int j = start; j <= i; j++)
            {
                curr_sequence[j - start] = values[j];
            }
            if (!seen[curr_sequence])
            {
                sequences[curr_sequence] += curr;

                seen[curr_sequence] = true;
            }
            


            start++;
        }
    }

}
