#include <CacheSet.hpp>
#include <MOESICache.hpp>
#include <iostream>

MOESICache::MOESICache(_id id, Bus* pbus)
		: Cache(id, pbus) {

}

void MOESICache::read_request(_address address) {
	std::cout << "Cache " << id << ": " << "Read request address MOESI "
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

void MOESICache::write_request(_address address) {
	std::cout << "Cache " << id << ": " << "Read request address MOESI "
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
		}
	}

}

bool MOESICache::handle_bus_request(Bus::BusRequest request) {
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
