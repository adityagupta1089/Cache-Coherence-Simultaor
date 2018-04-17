#include <Bus.hpp>
#include <MESICache.hpp>
#include <MOESICache.hpp>
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
				cache = new MESICache(i, bus);
				break;
			case MOESI:
				cache = new MOESICache(i, bus);
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

