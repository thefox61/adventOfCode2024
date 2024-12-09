#include "day9.h"

std::vector<int> loadFileSystem(std::string input_file)
{

	std::ifstream the_file(input_file);

	std::string temp;

	std::vector<int> file_system;

	while (std::getline(the_file, temp))
	{
		for (int i = 0; i < temp.length(); i++)
		{
			file_system.emplace_back(temp[i] - '0');
		}
	}
    return file_system;
}

std::vector<int> sparseConversion(std::vector<int>& file_system)
{
	std::vector<int> sparse_file_system;
	int count = 0;
	for (int i = 0; i < file_system.size(); i+=2)
	{
		int file_size = file_system[i];
		for (int j = 0; j < file_size; j++)
		{
			sparse_file_system.emplace_back(count);
		}
		if (file_size > 0)
		{
			count++;
		}
		

		if (i + 1 != file_system.size())
		{
			int free_space = file_system[i + 1];
			for (int j = 0; j < free_space; j++)
			{
				sparse_file_system.emplace_back(-1);
			}

		}
		
	}
	return sparse_file_system;
}

std::vector<int> sparseConversionTwo(std::vector<int>& file_system, std::map<int, fileBlock>& free_blocks, std::vector<fileBlock>& file_blocks)
{
	std::vector<int> sparse_file_system;
	int count = 0;
	for (int i = 0; i < file_system.size(); i += 2)
	{
		int file_size = file_system[i];
		int start_index = sparse_file_system.size();
		for (int j = 0; j < file_size; j++)
		{
			sparse_file_system.emplace_back(count);
		}
		if (file_size > 0)
		{
			file_blocks.emplace_back(count, file_size, fileBlock::blocktype::file, start_index);
			count++;
		}


		if (i + 1 != file_system.size())
		{
			int free_space = file_system[i + 1];
			start_index = sparse_file_system.size();
			for (int j = 0; j < free_space; j++)
			{
				sparse_file_system.emplace_back(-1);
			}

			free_blocks[start_index] = fileBlock(count, free_space, fileBlock::blocktype::free, start_index);
		}

	}

	return sparse_file_system;
}

std::vector<int> compactFileSystem(std::vector<int>& sparse_file_system)
{
	int file_system_size = sparse_file_system.size();
	int next_free_space = 0;
	int next_file = sparse_file_system.size() - 1;

	while (next_free_space < next_file)
	{
		while (sparse_file_system[next_free_space] != -1 && next_free_space < file_system_size)
		{
			next_free_space++;
		}

		while (sparse_file_system[next_file] == -1 && next_file > 0)
		{
			next_file--;
		}

		if (next_free_space < next_file)
		{
			sparse_file_system[next_free_space] = sparse_file_system[next_file];
			sparse_file_system[next_file] = -1;
		}
	
	}

	return sparse_file_system;
}

std::vector<int> compactFileSystemTwo(std::vector<int>& sparse_file_system, std::map<int, fileBlock>& free_blocks, std::vector<fileBlock>& file_blocks)
{
	std::map<int, fileBlock>::iterator it;
	for (int i = file_blocks.size() - 1; i >= 0; i--)
	{
		fileBlock* curr_file = &file_blocks[i];
		 
		it = free_blocks.begin();

		while (it != free_blocks.end())
		{
			if (it->second.size >= curr_file->size && it->second.start_index < curr_file->start_index)
			{
				fileBlock* curr_block = &it->second;

				for (int k = 0; k < curr_file->size; k++)
				{
					sparse_file_system[curr_block->start_index + k] = curr_file->id;
					sparse_file_system[curr_file->start_index + k] = -1;
				}

				free_blocks[curr_file->start_index] = fileBlock(curr_block->id, curr_file->size, fileBlock::blocktype::free, curr_file->start_index);

				int new_block_size = curr_block->size - curr_file->size;
				if (new_block_size > 0)
				{
					int new_start_index = curr_block->start_index + curr_file->size;

					free_blocks[new_start_index] = fileBlock(curr_block->id, new_block_size, fileBlock::blocktype::free, new_start_index);

				}
				free_blocks.erase(it);

				

				break;
			}
			it++;

		}

	}

	return sparse_file_system;
}

long long computeChecksum(std::vector<int>& file_system)
{
	std::vector<int> sparse_file_system = sparseConversion(file_system);

	compactFileSystem(sparse_file_system);

	long long check_sum = 0;

	for (long long i = 0; i < sparse_file_system.size(); i++)
	{
		if (sparse_file_system[i] == -1)
		{
			continue;
		}

		check_sum += i * sparse_file_system[i];
	}


	return check_sum;
}

long long computeChecksumTwo(std::vector<int>& file_system)
{
	std::map<int, fileBlock> free_blocks; 
	std::vector<fileBlock> file_blocks;

	std::vector<int> sparse_file_system = sparseConversionTwo(file_system, free_blocks, file_blocks);

	compactFileSystemTwo(sparse_file_system, free_blocks, file_blocks);


	long long check_sum = 0;

	for (long long i = 0; i < sparse_file_system.size(); i++)
	{
		if (sparse_file_system[i] == -1)
		{
			continue;
		}

		check_sum += i * sparse_file_system[i];
	}


	bool breakpoint = false;

	return check_sum;
}
