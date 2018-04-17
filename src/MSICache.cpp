#include <CacheSet.hpp>
#include <MSICache.hpp>
#include <iostream>

class Bus;

MSICache::MSICache(_id id, Bus* pbus)
		: Cache(id, pbus) {

}

void MSICache::read_request(_address address) {
	std::cout << "Cache " << id << ": " << "Read request address MSI "
			<< std::hex << address << "\n";
	CacheSet::CacheLine* line = get_line(address);
	if (!line) {
		Bus::BusRequest request =
			{ id, Bus::read_miss, address, nullptr };
		std::cout << "Cache " << id << ": " << "Placed a read miss on bus\n";
		require_share_data = true;
		bus->push_request(request);
		/* This blocking call may result in handle_bus_request() to cache the
		 * data */
		line = get_line(address);
		if (!line) {
			std::cout << "Cache " << id << ": "
					<< "Fetched from secondary storage\n";
			_id set_id = get_set_id(request.address);
			sets[set_id]->add_line(request.address, CacheSet::MODIFIED);
		} else {
			std::cout << "Cache " << id << ": " << "Snooped from other cache\n";
		}
	} else {
		switch (line->state) {
			case CacheSet::MODIFIED:
			case CacheSet::SHARED:
				std::cout << "Cache " << id << ": "
						<< "Read data in local cache\n";
				break;
			case CacheSet::INVALID: {
				Bus::BusRequest request =
					{ id, Bus::read_miss, address, nullptr };
				std::cout << "Cache " << id << ": "
						<< "Placed a read miss on bus\n";
				bus->push_request(request);
				break;
			}
			default:
				std::cerr << "Cache " << id << ": " << "Invalid cache state "
						<< static_cast<char>(line->state) << " for MSI Cache\n";
				break;
		}
	}

}

void MSICache::write_request(_address address) {
	std::cout << "Cache " << id << ": " << "Write request address MSI "
			<< std::hex << address << "\n";
	CacheSet::CacheLine* line = get_line(address);
	if (!line) {
		Bus::BusRequest request =
			{ id, Bus::write_miss, address, nullptr };
		std::cout << "Cache " << id << ": " << "Placed write miss on bus\n";
		bus->push_request(request);
	} else {
		switch (line->state) {
			case CacheSet::MODIFIED:
				std::cout << "Cache " << id << ": "
						<< "Wrote data in local cache\n";
				break;
			case CacheSet::SHARED: {
				Bus::BusRequest request =
					{ id, Bus::invalidate, address, nullptr };
				std::cout << "Cache " << id << ": "
						<< "Placed invalidate on bus\n";
				bus->push_request(request);
				break;
			}
			case CacheSet::INVALID: {
				Bus::BusRequest request =
					{ id, Bus::write_miss, address, nullptr };
				std::cout << "Cache " << id << ": "
						<< "Placed write miss on bus\n";
				bus->push_request(request);
				break;
			}
			default:
				std::cerr << "Cache " << id << ": " << "Invalid cache state "
						<< static_cast<char>(line->state) << " for MSI Cache\n";
				break;
		}
	}
}

bool MSICache::handle_bus_request(Bus::BusRequest request) {
	CacheSet::CacheLine* line = get_line(request.address);
	if (!line && request.operation != Bus::share_data) return false;
	if (request.operation == Bus::share_data && !require_share_data) return false;
	std::cout << "\tCache " << id << ": " << "Bus request address MSI "
			<< std::hex << request.address << " from Cache " << request.cache_id
			<< "\n\t";
	switch (request.operation) {
		case Bus::read_miss:
			if (line->state == CacheSet::SHARED) {
				std::cout << "Cache " << id << ": "
						<< "Allowing shared cache/memory to service read miss\n";
			} else if (line->state == CacheSet::MODIFIED) {
				Bus::BusRequest re_request =
					{ id, Bus::share_data, request.address, line };
				std::cout << "Cache " << id << ": " << "Shared cache block\n";
				bus->push_request(re_request);
				return true;
			}
			break;
		case Bus::write_miss:
			if (line->state == CacheSet::SHARED) {
				line->invalidate();
				std::cout << "Cache " << id << ": "
						<< "Attempt to write shared block. Invalidated Cache "
								"block\n";
			} else if (line->state == CacheSet::MODIFIED) {
				line->invalidate();
				std::cout << "Cache " << id
						<< ": Attempt to write block that is exclusive elsewhere, wrote back the cache block and invalidated cache block\n";
			}
			break;
		case Bus::invalidate:
			line->invalidate();
			std::cout << "Cache " << id << ": "
					<< "Attempt to write shared block. Invalidated Cache "
							"block\n";
			break;
		case Bus::share_data: {
			std::cout << "Cache " << id << ": "
					<< "Received cache block from other cache\n";
			_id set_id = get_set_id(request.address);
			sets[set_id]->add_line(request.address, CacheSet::SHARED);
			break;
		}
	}
	return false;
}
