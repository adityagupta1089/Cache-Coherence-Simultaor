#include <Simulator.hpp>
#include <iostream>

Simulator::Simulator() {

}

void Simulator::push_request(_operation operation, _address address, _id id) {
	std::cout << "Operation " << static_cast<char>(operation) << " for address "
			<< std::hex << address << " on processor " << id << "\n";
}

