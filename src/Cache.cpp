#include <Cache.hpp>

Cache::Cache(_id pid, Bus* pbus, Simulator::Statistics& pstats)
		: id(pid), bus(pbus), stats(pstats), require_share_data(false), received_share_data(
				false) {
	for (unsigned i = 0; i < SETS; i++) {
		sets.push_back(new CacheSet(pstats));
	}
}

_id Cache::get_set_id(_address address) {
	return address >> (INDEX_BITS + OFFSET_BITS);
}

CacheSet::CacheLine* Cache::get_line(_address address) {
	return sets[get_set_id(address)]->get_line(address);
}

bool Cache::push_bus_request(Bus::BusRequest request) {
	if (request.cache_id != id) {
		if (handle_bus_request(request)) {
			return true;
		}
	}
	return false;
}
