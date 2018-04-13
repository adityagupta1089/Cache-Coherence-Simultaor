#include <MESICache.hpp>
#include <MOESICache.hpp>
#include <MSICache.hpp>
#include <Simulator.hpp>
#include <iostream>

Simulator::Simulator() {
	for (_id i = 0; i < PROCESSORS; i++) {
		Cache* cache;
		switch (PROTOCOL) {
			case MSI:
				cache = new MSICache(i);
				break;
			case MESI:
				cache = new MESICache(i);
				break;
			case MOESI:
				cache = new MOESICache(i);
				break;
		}
		caches.push_back(cache);
	}
}

void Simulator::push_request(_operation operation, _address address, _id id) {
	switch (operation) {
		case READ:
			caches[id]->read(address);
			break;
		case WRITE:
			caches[id]->write(address);
			break;
	}
}

