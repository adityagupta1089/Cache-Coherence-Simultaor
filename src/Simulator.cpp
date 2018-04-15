#include <Bus.hpp>
#include <MSICache.hpp>
#include <Simulator.hpp>

Simulator::Simulator() {
	bus = new Bus(caches);
	for (_id i = 0; i < PROCESSORS; i++) {
		Cache* cache;
		switch (PROTOCOL) {
			case MSI:
				cache = new MSICache(i, bus);
				break;
			case MESI:
				//cache = new MESICache(i, bus);
				break;
			case MOESI:
				//cache = new MOESICache(i, bus);F
				break;
		}
		caches.push_back(cache);
	}
}

void Simulator::push_request(_operation operation, _address address, _id id) {
	switch (operation) {
		case READ:
			caches[id]->push_read_request(address);
			break;
		case WRITE:
			caches[id]->push_write_request(address);
			break;
	}
}

