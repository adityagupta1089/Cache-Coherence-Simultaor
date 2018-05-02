#include <CacheSet.hpp>
#include <MESICache.hpp>
#include <iostream>

class Bus;

MESICache::MESICache(_id id, Bus* pbus)
		: Cache(id, pbus) {

}

void MESICache::read_request(_address address) {
	std::cout << "Cache " << id << ": " << "Read request address MESI "
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
			sets[set_id]->add_line(request.address, CacheSet::EXCLUSIVE);
		} else {
			std::cout << "Cache " << id << ": " << "Snooped from other cache\n";
		}
	} else {
		switch (line->state) {
			case CacheSet::MODIFIED:
			case CacheSet::EXCLUSIVE:
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
				if (!received_share_data) {
					line->state = CacheSet::MODIFIED;
					received_share_data = false;
				}
				break;
			}
			default:
				std::cerr << "Cache " << id << ": " << "Invalid cache state "
						<< static_cast<char>(line->state) << " for MSI Cache\n";
				break;
		}
	}

}

void MESICache::write_request(_address address) {
	std::cout << "Cache " << id << ": " << "Read request address MESI "
			<< std::hex << address << "\n";
	CacheSet::CacheLine* line = get_line(address);
	if (!line) {
		Bus::BusRequest request =
			{ id, Bus::write_miss, address, nullptr };
		std::cout << "Cache " << id << ": " << "Placed write miss on bus\n";
		bus->push_request(request);
		_id set_id = get_set_id(request.address);
		sets[set_id]->add_line(request.address, CacheSet::MODIFIED);
		std::cout << "Cache " << id << ": " << "Wrote data in local cache\n";
	} else {
		switch (line->state) {
			case CacheSet::MODIFIED:
				std::cout << "Cache " << id << ": "
						<< "Wrote data in local cache\n";
				break;
			case CacheSet::EXCLUSIVE:
				std::cout << "Cache " << id << ": "
						<< "Wrote data in local cache\n";
				line->state = CacheSet::MODIFIED;
				std::cout << "Cache " << id << ": "
						<< "Changed state to modified\n";
				break;
			case CacheSet::SHARED: {
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
				std::cerr << "Cache " << id << ": " << "Invalid cache state "
						<< static_cast<char>(line->state)
						<< " for MESI Cache\n";
				break;
		}
	}

}

bool MESICache::handle_bus_request(Bus::BusRequest request) {
	CacheSet::CacheLine* line = get_line(request.address);
	if (!line && request.operation != Bus::share_data) return false;
	switch (request.operation) {
		case Bus::read_miss:
			switch (line->state) {
				case CacheSet::MODIFIED:
				case CacheSet::EXCLUSIVE: {
					Bus::BusRequest re_request =
						{ id, Bus::share_data, request.address, line };
					std::cout << "Cache " << id << ": "
							<< "Shared cache block\n";
					bus->push_request(re_request);
					line->state = CacheSet::SHARED;
					std::cout << "Cache " << id << ": "
							<< "Changed state to Shared\n";
					return true;
				}
				case CacheSet::SHARED:
				case CacheSet::INVALID:
					/* No change */
					break;
				default:
					std::cerr << "Cache " << id << ": "
							<< "Invalid cache state "
							<< static_cast<char>(line->state)
							<< " for MESI Cache\n";
					break;
			}
			break;
		case Bus::write_miss:
			switch (line->state) {
				case CacheSet::MODIFIED:
					break;
				case CacheSet::EXCLUSIVE:
					break;
				case CacheSet::SHARED:
					break;
				case CacheSet::INVALID:
					break;
				default:
					std::cerr << "Cache " << id << ": "
							<< "Invalid cache state "
							<< static_cast<char>(line->state)
							<< " for MESI Cache\n";
					break;
			}
			break;
		case Bus::invalidate:

			break;
		case Bus::share_data:
			received_share_data = true;
			std::cout << "Cache " << id << ": "
					<< "Received cache block from other cache\n";
			_id set_id = get_set_id(request.address);
			sets[set_id]->add_line(request.address, CacheSet::SHARED);
			break;
	}
	return false;
}
