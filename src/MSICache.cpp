#include <CacheSet.hpp>
#include <MSICache.hpp>
#include <stddef.h>
#include <iostream>

class Bus;

MSICache::MSICache(_id id, Bus* pbus)
		: Cache(id, pbus) {

}

void MSICache::push_read_request(_address address) {
	std::cout << "Read address MSI " << std::hex << address << "\n";
	CacheSet::CacheLine* line;
	if ((line = get_line(address)) != NULL) {
		Bus::BusRequest request =
			{ id, Bus::read_miss, address, nullptr };
		bus->push_request(request);
		std::cout << "Placed a read miss on bus\n";
	} else {
		switch (line->state) {
			case CacheSet::MODIFIED:
			case CacheSet::SHARED:
				std::cout << "Read data in local cache\n";
				break;
			case CacheSet::INVALID: {
				Bus::BusRequest request =
					{ id, Bus::read_miss, address, nullptr };
				bus->push_request(request);
				std::cout << "Placed a read miss on bus\n";
				break;
			}
			default:
				std::cerr << "Invalid cache state "
						<< static_cast<char>(line->state) << " for MSI Cache\n";
				break;
		}
	}

}

void MSICache::push_write_request(_address address) {
	std::cout << "Write address MSI " << std::hex << address << "\n";
	CacheSet::CacheLine* line = get_line(address);
	_id set_id = get_set_id(address);
	if (!line) {
		sets[set_id]->add_line(address, CacheSet::SHARED);
	} else {
		switch (line->state) {
			case CacheSet::MODIFIED:
				std::cout << "Wrote data in local cache\n";
				break;
			case CacheSet::SHARED: {
				Bus::BusRequest request =
					{ id, Bus::invalidate, address, nullptr };
				bus->push_request(request);
				std::cout << "Placed invalidate on bus\n";
				break;
			}
			case CacheSet::INVALID: {
				Bus::BusRequest request =
					{ id, Bus::write_miss, address, nullptr };
				bus->push_request(request);
				std::cout << "Placed write miss on bus\n";
				break;
			}
			default:
				std::cerr << "Invalid cache state "
						<< static_cast<char>(line->state) << " for MSI Cache\n";
				break;
		}
	}
}

void MSICache::handle_bus_request(Bus::BusRequest request) {
	CacheSet::CacheLine* line = get_line(request.address);
	switch (request.operation) {
		case Bus::read_miss:
			if (line->state == CacheSet::SHARED) {
				std::cout << "Allowing shared cache/memory to service read "
						"miss\n";
			} else if (line->state == CacheSet::MODIFIED) {
				Bus::BusRequest re_request =
					{ id, Bus::share_data, request.address, line };
				bus->push_request(re_request);
			}
			break;
		case Bus::write_miss:
			if (line->state == CacheSet::SHARED) {
				line->invalidate();
				std::cout << "Attempt to write shared block. Invalidated Cache "
						"block\n";
			} else if (line->state == CacheSet::MODIFIED) {
				line->invalidate();
				std::cout << "Attempt to write block that is exclusive "
						"elsewhere, wrote back the cache block and invalidated "
						"cache block\n";
			}
			break;
		case Bus::invalidate:
			line->invalidate();
			std::cout << "Attempt to write shared block. Invalidated Cache "
					"block\n";
			break;
		default:
			std::cout << "Don't know what to do with this Bus request \n";
	}
}
