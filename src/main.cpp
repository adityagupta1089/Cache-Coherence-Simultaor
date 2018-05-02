#include <Constants.hpp>
#include <stdlib.h>
#include <Simulator.hpp>
#include <fstream>
#include <iostream>

class Simulator;

bool valid(char, _address, _id);

int main(int argc, char** argv) {
	if (argc < 2) {
		std::cerr << "Input format: " << argv[0] << " <input_file>\n";
		exit(1);
	}

	Simulator simulator;

	std::ifstream in;
	in.open(argv[1]);

	if (!in) {
		std::cerr << "Unable to open file " << argv[1] << "\n";
		exit(1);
	} else {
		char operation;
		_address address;
		_id processor;
		while (in >> operation >> std::hex >> address >> processor) {
			std::cout << "\n-> Operation " << operation << ", address "
					<< std::hex << address << ", Processor " << processor
					<< "\n";
			if (!valid(operation, address, processor)) exit(1);
			simulator.push_request(static_cast<_operation>(operation), address,
					processor);
		}
	}

	in.close();

	simulator.print_statistics();

	return 0;
}

bool valid(char operation, _address address, _id id) {
	if (operation != 'R' && operation != 'W') {
		std::cerr << "Invalid operation! Only 'R' or 'W' accepted\n";
		return false;
	}
	if (address >= MEMORY_SIZE) {
		std::cerr << "Memory location out of bounds! (0, " << std::hex
				<< MEMORY_SIZE << ")\n";
		return false;
	}
	if (id >= PROCESSORS) {
		std::cerr << "Invalid processor ID! (0, " << (PROCESSORS - 1) << "\n";
		return false;
	}
	return true;

}
