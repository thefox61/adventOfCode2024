#include "day17.h"
#include <cmath>

program loadProgram(std::string input_file)
{
    std::ifstream the_file(input_file);

    std::string temp;

    program the_program;


    // register A
    std::getline(the_file, temp);

    int num_start = temp.find_first_of(':') + 1;
    the_program.A = stol(temp.substr(num_start, temp.length() - num_start));

    // register B
    std::getline(the_file, temp);

    num_start = temp.find_first_of(':') + 1;
    the_program.B = stol(temp.substr(num_start, temp.length() - num_start));

    // register C
    std::getline(the_file, temp);

    num_start = temp.find_first_of(':') + 1;
    the_program.C = stol(temp.substr(num_start, temp.length() - num_start));

    // empty line
    std::getline(the_file, temp);


    // instructions/ops
    std::getline(the_file, temp);

    num_start = temp.find_first_of(':') + 2;
    for (int i = num_start; i < temp.length(); i += 2)
    {
        //std::string num = temp.substr(i, 1);
        the_program.instructions.emplace_back(std::stoi(temp.substr(i, 1)));
    }

    return the_program;
}

long long comboOpValue(program& the_program, int op)
{
    switch (op) 
    {
    case 0:
        return 0;
        
    case 1:
        return 1;

    case 2:
        return 2;
    
    case 3:
        return 3;
    case 4:
        return the_program.A;
    case 5:
        return the_program.B;
    case 6:
        return the_program.C;
    }

    // error!
    return -1;
}

void adv(program& the_program)
{
    int op = the_program.instructions[the_program.instruction_pointer + 1];
    long op_value = comboOpValue(the_program, op);

    the_program.A = the_program.A / std::pow(2, op_value);
}

void bxl(program& the_program)
{
    the_program.B = the_program.B ^ the_program.instructions[the_program.instruction_pointer + 1];
}

void bst(program& the_program)
{
    the_program.B = comboOpValue(the_program, the_program.instructions[the_program.instruction_pointer + 1]) % 8;
}

void jnz(program& the_program)
{
    if (the_program.A != 0)
    {
        the_program.instruction_pointer = the_program.instructions[the_program.instruction_pointer + 1];

        the_program.instruction_pointer -= 2;
    }
}

void bxc(program& the_program)
{
    the_program.B = the_program.B ^ the_program.C;
}

void out(program& the_program)
{
    the_program.out_buf.emplace_back(comboOpValue(the_program, the_program.instructions[the_program.instruction_pointer + 1]) % 8);
}

void bdv(program& the_program)
{
    int op = the_program.instructions[the_program.instruction_pointer + 1];
    long op_value = comboOpValue(the_program, op);

    the_program.B = the_program.A / std::pow(2, op_value);
}

void cdv(program& the_program)
{
    int op = the_program.instructions[the_program.instruction_pointer + 1];
    long op_value = comboOpValue(the_program, op);

    the_program.C = the_program.A / std::pow(2, op_value);
}

std::string executeProgram(program& the_program)
{
    while (the_program.instruction_pointer < the_program.instructions.size())
    {
        switch (the_program.instructions[the_program.instruction_pointer])
        {
            case 0:
                adv(the_program);
                break;

            case 1:
                bxl(the_program);
                break;

            case 2:
                bst(the_program);
                break;

            case 3:
                jnz(the_program);
                break;

            case 4:
                bxc(the_program);
                break;

            case 5:
                out(the_program);
                break;

            case 6:
                bdv(the_program);
                break;

            case 7:
                cdv(the_program);
                break;
        }

        the_program.instruction_pointer += 2;
    }


    std::stringstream output_string;

    for (int i = 0; i < the_program.out_buf.size(); i++)
    {
        output_string << std::to_string(the_program.out_buf[i]);

        if (i + 1 != the_program.out_buf.size())
        {
            output_string << ",";
        }
    }

    return output_string.str();
}

long long getFirstProgramOutput(program& the_program)
{
    while (the_program.instruction_pointer < the_program.instructions.size())
    {
        switch (the_program.instructions[the_program.instruction_pointer])
        {
        case 0:
            adv(the_program);
            break;

        case 1:
            bxl(the_program);
            break;

        case 2:
            bst(the_program);
            break;

        case 3:
            jnz(the_program);
            break;

        case 4:
            bxc(the_program);
            break;

        case 5:
            out(the_program);
            return the_program.out_buf[0];
            break;

        case 6:
            bdv(the_program);
            break;

        case 7:
            cdv(the_program);
            break;
        }

        the_program.instruction_pointer += 2;
    }

    return 0;
}


long long findAValue(program& the_program)
{
    long long A = LLONG_MAX;

    long initial_b = the_program.B;
    long initial_c = the_program.C;

    std::set <long long> valid_values;
    valid_values.insert(0);

    for (int i = the_program.instructions.size() - 1; i >= 0; i--)
    {
        std::set <long long> cur_values;
        for (long long val : valid_values)
        {
            for (int j = 0; j < 8; j++)
            {
                long long tempA = val << 3;
                tempA = tempA | j;

                the_program.A = tempA;
                the_program.B = initial_b;
                the_program.C = initial_c;

                the_program.instruction_pointer = 0;
                the_program.out_buf.clear();

                long long result = getFirstProgramOutput(the_program);


                if (result == the_program.instructions[i])
                {
                    cur_values.insert(tempA);
                }
            }
        }
        valid_values = cur_values;

    }
    for (long long val : valid_values)
    {
        if (val < A)
        {
            A = val;
        }
    }


    return A;
}



