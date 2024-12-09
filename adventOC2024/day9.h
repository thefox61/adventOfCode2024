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

	unsigned int id;

	int size;

	blocktype type;

	int start_index;
	
};

std::vector<int> loadFileSystem(std::string input_file);

std::vector<int> sparseConversion(std::vector<int>& file_system);

std::vector<int> sparseConversionTwo(std::vector<int>& file_system, std::map<int, fileBlock>& free_blocks, std::vector<fileBlock>& file_blocks);

std::vector<int> compactFileSystem(std::vector<int>& sparse_file_system);

std::vector<int> compactFileSystemTwo(std::vector<int>& sparse_file_system, std::map<int, fileBlock>& free_blocks, std::vector<fileBlock>& file_blocks);


long long computeChecksum(std::vector<int>& file_system);

long long computeChecksumTwo(std::vector<int>& file_system);




