#include <CacheSet.hpp>
#include <MESICache.hpp>
#include <iostream>

class Bus;

MESICache::MESICache(_id id, Bus* pbus, Simulator::Statistics& stats)
		: Cache(id, pbus, stats) {

}

void MESICache::read_request(_address address) {
	std::cout << "Cache " << id << ": " << "Read request address MESI "
			<< std::hex << address << "\n";
	CacheSet::CacheLine* line = get_line(address);
	if (!line) {
		stats.misses++;
		std::cout << "Cache " << id << ": " << "Line not present\n";
		Bus::BusRequest request =
			{ id, Bus::read_miss, address, nullptr };
		std::cout << "Cache " << id << ": " << "Placed a read miss on bus\n";
		require_share_data = true;
		/* This blocking call may result in handle_bus_request() to cache the
		 * data */
		bus->push_request(request);
		require_share_data = false;
		line = get_line(address);
		if (!line) {
			std::cout << "Cache " << id << ": "
					<< "Fetched from secondary storage\n";
			_id set_id = get_set_id(request.address);
			sets[set_id]->add_line(request.address, CacheSet::EXCLUSIVE);
		} else {
			std::cout << "Cache " << id << ": " << "Snooped from other cache\n";
		}
	} else {
		std::cout << "Cache " << id << ": " << "Line in state "
				<< static_cast<char>(line->state) << "\n";
		switch (line->state) {
			case CacheSet::MODIFIED:
			case CacheSet::EXCLUSIVE:
			case CacheSet::SHARED:
				stats.hits++;
				std::cout << "Cache " << id << ": "
						<< "Read data in local cache\n";
				break;
			case CacheSet::INVALID: {
				stats.misses++;
				Bus::BusRequest request =
					{ id, Bus::read_miss, address, nullptr };
				std::cout << "Cache " << id << ": "
						<< "Placed a read miss on bus\n";
				require_share_data = true;
				bus->push_request(request);
				require_share_data = false;
				if (!received_share_data) {
					line->state = CacheSet::EXCLUSIVE;
					received_share_data = false;
				}
				break;
			}
			default:
				break;
		}
	}

}

void MESICache::write_request(_address address) {
	std::cout << "Cache " << id << ": " << "Write request address MESI "
			<< std::hex << address << "\n";
	CacheSet::CacheLine* line = get_line(address);
	if (!line) {
		stats.misses++;
		std::cout << "Cache " << id << ": " << "Line not present\n";
		Bus::BusRequest request =
			{ id, Bus::write_miss, address, nullptr };
		std::cout << "Cache " << id << ": " << "Placed write miss on bus\n";
		bus->push_request(request);
		_id set_id = get_set_id(request.address);
		sets[set_id]->add_line(request.address, CacheSet::MODIFIED);
		std::cout << "Cache " << id << ": " << "Wrote data in local cache\n";
	} else {
		std::cout << "Cache " << id << ": " << "Line in state "
				<< static_cast<char>(line->state) << "\n";
		switch (line->state) {
			case CacheSet::MODIFIED:
				stats.hits++;
				std::cout << "Cache " << id << ": "
						<< "Wrote data in local cache\n";
				break;
			case CacheSet::EXCLUSIVE:
				stats.hits++;
				std::cout << "Cache " << id << ": "
						<< "Wrote data in local cache\n";
				line->state = CacheSet::MODIFIED;
				std::cout << "Cache " << id << ": "
						<< "Changed state to modified\n";
				break;
			case CacheSet::SHARED: {
				stats.hits++;
				Bus::BusRequest request =
					{ id, Bus::invalidate, address, nullptr };
				std::cout << "Cache " << id << ": "
						<< "Placed invalidate on bus\n";
				bus->push_request(request);
				line->state = CacheSet::MODIFIED;
				std::cout << "Cache " << id << ": "
						<< "Changed state to Modified\n";
				break;
			}
			case CacheSet::INVALID: {
				stats.misses++;
				Bus::BusRequest request =
					{ id, Bus::write_miss, address, nullptr };
				std::cout << "Cache " << id << ": "
						<< "Placed write miss on bus\n";
				bus->push_request(request);
				line->state = CacheSet::MODIFIED;
				std::cout << "Cache " << id << ": "
						<< "Changed state to Modified\n";
				break;
			}
			default:
				break;
		}
	}
}

bool MESICache::handle_bus_request(Bus::BusRequest request) {
	CacheSet::CacheLine* line = get_line(request.address);
	if (!line && request.operation != Bus::share_data) return false;
	if (request.operation == Bus::share_data && !require_share_data) return false;
	std::cout << "Cache " << id << ": " << "Bus request address MESI "
			<< std::hex << request.address << " from Cache " << request.cache_id
			<< "\n";
	switch (request.operation) {
		case Bus::read_miss:
			switch (line->state) {
				case CacheSet::MODIFIED:
				case CacheSet::EXCLUSIVE:
				case CacheSet::SHARED: {
					Bus::BusRequest re_request =
						{ id, Bus::share_data, request.address, line };
					std::cout << "Cache " << id << ": "
							<< "Shared cache block\n";
					bus->push_request(re_request);
					line->state = CacheSet::SHARED;
					std::cout << "Cache " << id << ": "
							<< "Changed state to Shared\n";
					return true;
					break;
				}
				case CacheSet::INVALID:
					std::cout << "Cache " << id << ": " << "No change\n";
					break;
				default:
					break;
			}
			break;
		case Bus::write_miss:
			switch (line->state) {
				case CacheSet::SHARED:
					line->invalidate();
					std::cout << "Cache " << id << ": "
							<< "Attempt to write shared block. Invalidated Cache "
									"block\n";
					break;
				case CacheSet::EXCLUSIVE:
				case CacheSet::MODIFIED:
					line->invalidate();
					stats.flushes++;
					std::cout << "Cache " << id
							<< ": Attempt to write block that is exclusive elsewhere, wrote back the cache block and invalidated cache block\n";
					break;
				case CacheSet::INVALID:
					std::cout << "Cache " << id << ": " << "No change\n";
					break;
				default:
					break;
			}
			break;
		case Bus::invalidate:
			line->invalidate();
			std::cout << "Cache " << id << ": "
					<< "Attempt to write shared block. Invalidated Cache "
							"block\n";
			break;
		case Bus::share_data: {
			received_share_data = true;
			std::cout << "Cache " << id << ": "
					<< "Received cache block from other cache\n";
			if (!line) {
				_id set_id = get_set_id(request.address);
				sets[set_id]->add_line(request.address, CacheSet::SHARED);
			} else {
				line->state = CacheSet::SHARED;
			}
			break;
		}
	}
	return false;
}
