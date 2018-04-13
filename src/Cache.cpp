#include <Cache.hpp>

Cache::Cache(_id pid)
		: id(pid) {
	for (unsigned i = 0; i < SETS; i++) {
		sets.push_back(new CacheSet());
	}
}

_id Cache::get_set_id(_address address) {
	return address >> (INDEX_BITS + OFFSET_BITS);
}

CacheSet::CacheLine* Cache::get_line(_address address) {
	return sets[get_set_id(address)]->get_line(address);
}
