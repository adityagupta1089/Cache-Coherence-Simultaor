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

	} else {
		switch (line->state) {
			case CacheSet::MODIFIED:

				break;
			case CacheSet::OWNED:

				break;
			case CacheSet::EXCLUSIVE:

				break;
			case CacheSet::SHARED:

				break;
			case CacheSet::INVALID:

				break;
			default:
				break;
		}
	}

}

void MESICache::write_request(_address address) {
	std::cout << "Cache " << id << ": " << "Read request address MESI "
			<< std::hex << address << "\n";
	CacheSet::CacheLine* line = get_line(address);
	if (!line) {

	} else {
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

			break;
		case Bus::write_miss:

			break;
		case Bus::invalidate:

			break;
		case Bus::share_data:

			break;
	}
	return false;
}
