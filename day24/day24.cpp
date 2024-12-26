#include "day24.h"
#include <algorithm>

elvenDevice loadDevice(std::string input_file)
{
	std::ifstream the_file(input_file);

	std::string temp;


	elvenDevice elven_device;

	while (std::getline(the_file, temp))
	{
		if (temp.empty())
		{
			break;
		}


		int colon_loc = temp.find_first_of(':');

		std::string wire = temp.substr(0, colon_loc);

		int value = std::stoi(temp.substr(colon_loc + 1, temp.length() - colon_loc));

		elven_device.wires[wire] = value;
	}


	while (std::getline(the_file, temp))
	{
		// x41 XOR y41 -> twk
		std::vector<int> space_locations;

		for (int i = 0; i < temp.length(); i++)
		{
			if (temp[i] == ' ')
			{
				space_locations.emplace_back(i);
			}
		}

		if (space_locations.size() < 4)
		{
			continue;
		}

		std::string input_1 = temp.substr(0, space_locations[0]);

		std::string gate_type = temp.substr(space_locations[0] + 1, space_locations[1] - space_locations[0] - 1);

		std::string input_2 = temp.substr(space_locations[1] + 1, space_locations[2] - space_locations[1] - 1);

		std::string output = temp.substr(space_locations[3] + 1, temp.length() - space_locations[3] - 1);

		gate new_gate;

		new_gate.input_1 = input_1;
		new_gate.input_2 = input_2;

		new_gate.output = output;

		if (gate_type == "AND")
		{
			new_gate.type = gate::gateType::AND;
		}
		else if (gate_type == "OR")
		{
			new_gate.type = gate::gateType::OR;
		}
		else if (gate_type == "XOR")
		{
			new_gate.type = gate::gateType::XOR;
		}

		elven_device.gates.push_back(new_gate);
	}

	return elven_device;
}

unsigned long long evaluateDevice(elvenDevice device)
{
	while (!device.gates.empty())
	{
		gate curr_gate = device.gates.front();
		device.gates.pop_front();

		if (device.wires.count(curr_gate.input_1) == 0 || device.wires.count(curr_gate.input_2) == 0)
		{
			device.gates.push_back(curr_gate);
			continue;
		}

		int result;

		switch(curr_gate.type)
		{
			case gate::gateType::AND:
				result = device.wires[curr_gate.input_1] & device.wires[curr_gate.input_2];
				break;
			case gate::gateType::OR:
				result = device.wires[curr_gate.input_1] | device.wires[curr_gate.input_2];
				break;
			case gate::gateType::XOR:
				result = device.wires[curr_gate.input_1] ^ device.wires[curr_gate.input_2];
				break;
			default:
				std::cout << "something has gone wrong --  gate has no op" << std::endl;
				return 0;
		}

		device.wires[curr_gate.output] = result;

	}

	unsigned long long output_result = 0;


	std::map<std::string, int>::iterator it = device.wires.end();
	it--;

	while (it->first[0] == 'z')
	{
		output_result = output_result << 1;
		output_result += it->second;
		it--;
	}

	return output_result;
}

std::vector<gate> determineDependentGates(std::string wire, elvenDevice device)
{
	std::map<std::string, gate> output_to_gate;
	std::deque<gate>::iterator it = device.gates.begin();


	while (it != device.gates.end())
	{
		output_to_gate[it->output] = *it;
	}

	std::vector<gate> dependent_gates;


	std::deque<std::string> inputs;
	inputs.push_back(wire);

	while (!inputs.empty())
	{
		std::string curr_wire = inputs.front();
		inputs.pop_front();

		if (output_to_gate.count(curr_wire) != 0)
		{
			dependent_gates.push_back(output_to_gate[curr_wire]);
			inputs.push_back(output_to_gate[curr_wire].input_1);
			inputs.push_back(output_to_gate[curr_wire].input_2);
		}
	}

	return dependent_gates;
}

unsigned long long determineCorrectResult(elvenDevice device)
{
	unsigned long long x_value = 0;
	unsigned long long y_value = 0;

	std::map<std::string, int>::iterator it = device.wires.begin();

	while (it->first[0] == 'x')
	{
		x_value = x_value << 1;
		x_value += it->second;
		it++;
	}

	while (it != device.wires.end() && it->first[0] == 'y')
	{
		y_value = y_value << 1;
		y_value += it->second;
		it++;
	}


	return x_value + y_value;
}

std::vector<std::string> findIncorrectOutputWires(elvenDevice device)
{
	unsigned long long correct_result = determineCorrectResult(device);

	unsigned long long current_result = evaluateDevice(device);

	std::vector<std::string> incorrect_wires;

	std::vector<int> correct_bits;
	while (correct_result != 0)
	{
		int next_bit = correct_result & 1;

		correct_bits.emplace_back(next_bit);

		correct_result = correct_result >> 1;
	}

	std::vector<int> current_bits;
	while (current_result != 0)
	{
		int next_bit = current_result & 1;

		current_bits.emplace_back(next_bit);

		current_result = current_result >> 1;
	}

	for (int i = 0; i < correct_bits.size(); i++)
	{
		if (i < current_bits.size())
		{
			if (correct_bits[i] != current_bits[i])
			{
				incorrect_wires.emplace_back("z" + std::to_string(i));
			}
		}
		else
		{
			incorrect_wires.emplace_back("z" + std::to_string(i));
		}
	}

	return incorrect_wires;
}

void countGateTypes(elvenDevice device)
{
	std::map<gate::gateType, int> type_count;

	std::deque<gate>::iterator it = device.gates.begin();


	while (it != device.gates.end())
	{
		type_count[it->type]++;
		it++;

	}

	bool breakpoint = false;

}

std::set<std::string> identifySwappedWires(elvenDevice device)
{
	std::vector<fullAdder> adders;

	std::map<std::string, gate> output_to_gate;
	std::map<std::string, std::vector<gate>> input_to_gate;

	std::deque<gate>::iterator it = device.gates.begin();

	std::vector<gate> adderFirstXORs;

	std::vector<gate> adderFirstCarryAND;

	while (it != device.gates.end())
	{
		if (it->type == gate::gateType::XOR)
		{
			if (it->input_1[0] == 'x' && it->input_2[0] == 'y' || it->input_1[0] == 'y' && it->input_2[0] == 'x')
			{
				adderFirstXORs.push_back(*it);
			}
		}

		if (it->type == gate::gateType::AND)
		{
			if (it->input_1[0] == 'x' && it->input_2[0] == 'y' || it->input_1[0] == 'y' && it->input_2[0] == 'x')
			{
				adderFirstCarryAND.push_back(*it);
			}
		}

		input_to_gate[it->input_1].emplace_back(*it);
		input_to_gate[it->input_2].emplace_back(*it);
		output_to_gate[it->output] = *it;

		it++;
	}

	for (gate xorGate : adderFirstXORs)
	{
		fullAdder curr_adder;

		curr_adder.xor1 = xorGate;

		for (gate g : input_to_gate[xorGate.input_1])
		{
			if (g.type == gate::gateType::AND)
			{
				curr_adder.and1 = g;
				break;
			}
		}

		for (gate g : input_to_gate[xorGate.output])
		{
			if (g.type == gate::gateType::XOR)
			{
				curr_adder.xor2 = g;
			}
			else if (g.type == gate::gateType::AND)
			{
				curr_adder.and2 = g;
			}
		}


		for (gate g : input_to_gate[curr_adder.and1.output])
		{
			if (g.type == gate::gateType::OR)
			{
				curr_adder.or1 = g;
				break;
			}
		}
		for (gate g : input_to_gate[curr_adder.and2.output])
		{
			if (g.type == gate::gateType::OR)
			{
				curr_adder.or1 = g;
				break;
			}
		}

		// and1 output and xor1 output are incorrect (likely swapped)
		if (curr_adder.xor2.type == gate::gateType::NOP && curr_adder.and2.type == gate::gateType::NOP && curr_adder.or1.type == gate::gateType::NOP)
		{
			// check xor1 output for OR gate
			for (gate g : input_to_gate[curr_adder.xor1.output])
			{
				if (g.type == gate::gateType::OR)
				{
					curr_adder.or1 = g;
					break;
				}
			}

			// check and1 output for xor2 and and2
			for (gate g : input_to_gate[curr_adder.and1.output])
			{
				if (g.type == gate::gateType::XOR)
				{
					curr_adder.xor2 = g;
				}
				else if (g.type == gate::gateType::AND)
				{
					curr_adder.and2 = g;
				}
			}
		}


		adders.push_back(curr_adder);
	}

	int invalid_adder_count = 0;
	for (fullAdder adr : adders)
	{
		if (!validAdder(adr))
		{
			invalid_adder_count++;
		}
	}

	std::sort(adders.begin(), adders.end(), [](fullAdder a, fullAdder b)
		{
			return std::stoi(a.xor1.input_1.substr(1, 2)) < std::stoi(b.xor1.input_1.substr(1, 2));
		});
	

	std::set<std::string> swapped_wires = diagnoseAddingMachine(adders, output_to_gate, input_to_gate);


	return swapped_wires;
}

bool validAdder(fullAdder the_adder)
{
	if (the_adder.and1.type == gate::gateType::NOP ||
		the_adder.and2.type == gate::gateType::NOP ||
		the_adder.xor1.type == gate::gateType::NOP ||
		the_adder.xor2.type == gate::gateType::NOP ||
		the_adder.or1.type == gate::gateType::NOP)
	{
		return false;
	}

	return true;
}



std::set<std::string> diagnoseAddingMachine(std::vector<fullAdder>& adders, std::map<std::string, gate>& output_to_gate, std::map<std::string, std::vector<gate>>& input_to_gate)
{
	// adders vec is assumed to be sorted

	std::set<std::string> swapped_wires;
	std::string last_adder_carry_out = "";

	if (adders.empty())
	{
		return swapped_wires;
	}

	// first adder is special
	fullAdder& curr_adder = adders[0];
	if (curr_adder.xor1.output != "z00")
	{
		swapped_wires.insert(curr_adder.xor1.output);
	}
	last_adder_carry_out = curr_adder.and1.output;

	for (int i = 1; i < adders.size(); i++)
	{
		curr_adder= adders[i];

		if (curr_adder.xor1.output != curr_adder.xor2.input_1 && curr_adder.xor1.output != curr_adder.xor2.input_2)
		{
			swapped_wires.insert(curr_adder.xor1.output);
		}

		if (curr_adder.xor1.output != curr_adder.and2.input_1 && curr_adder.xor1.output != curr_adder.and2.input_2)
		{
			swapped_wires.insert(curr_adder.xor1.output);
		}

		if (i != 0 && last_adder_carry_out != curr_adder.xor2.input_1 && last_adder_carry_out != curr_adder.xor2.input_2)
		{
			if (curr_adder.xor2.type != gate::gateType::NOP)
			{
				swapped_wires.insert(last_adder_carry_out);
			}
		}

		if (i != 0 && last_adder_carry_out != curr_adder.and2.input_1 && last_adder_carry_out != curr_adder.and2.input_2)
		{
			if (curr_adder.and2.type != gate::gateType::NOP)
			{
				swapped_wires.insert(last_adder_carry_out);
			}
		}

		if (curr_adder.and1.output != curr_adder.or1.input_1 && curr_adder.and1.output != curr_adder.or1.input_2)
		{
			swapped_wires.insert(curr_adder.and1.output);
		}

		if (curr_adder.and2.output != curr_adder.or1.input_1 && curr_adder.and2.output != curr_adder.or1.input_2)
		{
			swapped_wires.insert(curr_adder.and2.output);
		}

		if (curr_adder.xor2.output.empty() || curr_adder.xor2.output[0] != 'z')
		{
			swapped_wires.insert(curr_adder.xor2.output);
		}

		last_adder_carry_out = curr_adder.or1.output;

	}

	return swapped_wires;
}
