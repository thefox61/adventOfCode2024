#pragma once

// save time includes
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <unordered_map>
#include <map>



struct fileBlock
{
	enum class blocktype
	{
		file,
		free
	};

	fileBlock(unsigned int id_, int size_, blocktype type_, int startIndex)
	{
		id = id_;
		size = size_;
		type = type_;
		start_index = startIndex;
	}

	fileBlock()
	{
		id = -1;
		size = 0;
		type = blocktype::free;
		start_index = -1;
	}

	int id;

	int size;

	blocktype type;

	int start_index;

	bool updated = false;

	fileBlock* next = NULL;
	fileBlock* prev = NULL;
	
};

struct fileSystem
{
	fileBlock* start = NULL;
	fileBlock* end = NULL;

	int num_files = 0;

	int num_blocks = 0;
};

std::vector<int> loadFileSystem(std::string input_file);

fileSystem loadFileSystemBlocks(std::string input_file);

std::vector<int> sparseConversion(std::vector<int>& file_system);

std::vector<int> sparseConversionTwo(std::vector<int>& file_system, std::map<int, fileBlock>& free_blocks, std::vector<fileBlock>& file_blocks);

std::vector<int> compactFileSystem(std::vector<int>& sparse_file_system);

std::vector<int> compactFileSystemTwo(std::vector<int>& sparse_file_system, std::map<int, fileBlock>& free_blocks, std::vector<fileBlock>& file_blocks);

void compactFileSystem(fileSystem& file_system);


long long computeChecksum(std::vector<int>& file_system);

long long computeChecksumTwo(std::vector<int>& file_system);




