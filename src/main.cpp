#include <Constants.hpp>
#include <Simulator.hpp>
#include <fstream>
#include <iostream>

class Simulator;

int main(int argc, char** argv) {
	if (argc < 2) {
		std::cerr << "Input format: " << argv[0] << " <input_file>\n";
		return 1;
	}

	Simulator simulator(PROTOCOL);

	std::ifstream in;
	in.open(argv[1]);

	if (!in) {
		std::cerr << "Unable to open file " << argv[1] << "\n";
		return 1;
	} else {
		char operation;
		_address address;
		_id processor;
		while (in >> operation >> std::hex >> address >> processor) {
			simulator.push_request(static_cast<_operation>(operation), address,
					processor);
		}
	}

	in.close();

	return 0;
}
