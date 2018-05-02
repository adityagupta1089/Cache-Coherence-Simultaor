#include <Bus.hpp>
#include <MESICache.hpp>
#include <MOESICache.hpp>
#include <MSICache.hpp>
#include <Simulator.hpp>
#include <iostream>

Simulator::Simulator()
		: stats(
			{ 0, 0, 0, 0, 0, 0 }) {
	bus = new Bus(caches, stats);
	for (_id i = 0; i < PROCESSORS; i++) {
		Cache* cache;
		switch (PROTOCOL) {
			case MSI:
				cache = new MSICache(i, bus, stats);
				break;
			case MESI:
				cache = new MESICache(i, bus, stats);
				break;
			case MOESI:
				cache = new MOESICache(i, bus, stats);
				break;
		}
		caches.push_back(cache);
	}
}

void Simulator::push_request(_operation operation, _address address, _id id) {
	switch (operation) {
		case READ:
			caches[id]->read_request(address);
			break;
		case WRITE:
			caches[id]->write_request(address);
			break;
	}
}

void Simulator::print_statistics() {
	std::cout << "\n-> Statistics\n" << std::dec;
	std::cout << "Total flushes: " << stats.flushes << "\n";
	std::cout << "Total hits: " << stats.hits << "\n";
	std::cout << "Total misses: " << stats.misses << "\n";
	std::cout << "Total evictions: " << stats.evicts << "\n";
	std::cout << "Total shares: " << stats.shares << "\n";
	std::cout << "Total bus requests: " << stats.bus_requests << "\n";
}

