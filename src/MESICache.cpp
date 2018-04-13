#include <MESICache.hpp>
#include <iostream>

MESICache::MESICache(_id id)
		: Cache(id) {

}

void MESICache::read(_address address) {
	std::cout << "Read address MESI " << std::hex << address << "\n";
}

void MESICache::write(_address address) {
	std::cout << "Write address MESI " << std::hex << address << "\n";
}

