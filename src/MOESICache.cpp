#include <Constants.hpp>
#include <MOESICache.hpp>
#include <iostream>

MOESICache::MOESICache(_id id)
		: Cache(id) {

}

void MOESICache::read(_address address) {
	std::cout << "Read address MOESI " << std::hex << address << "\n";
}

void MOESICache::write(_address address) {
	std::cout << "Write address MOESI " << std::hex << address << "\n";
}
