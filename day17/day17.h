#pragma once
// save time includes
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <unordered_map>
#include <set>


struct program
{
	long long A;
	long long B;
	long long C;

	std::vector<long> instructions;

	std::vector<long> out_buf;

	int instruction_pointer = 0;
};

program loadProgram(std::string input_file);

long long comboOpValue(program& the_program, int op);


void adv(program& the_program);

void bxl(program& the_program);

void bst(program& the_program);

void jnz(program& the_program);

void bxc(program& the_program);

void out(program& the_program);

void bdv(program& the_program);

void cdv(program& the_program);

std::string executeProgram(program& the_program);

long long getFirstProgramOutput(program& the_program);


long long findAValue(program& the_program);


