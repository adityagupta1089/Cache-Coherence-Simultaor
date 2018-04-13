#include <CacheSet.hpp>
#include <MSICache.hpp>
#include <stddef.h>
#include <iostream>

MSICache::MSICache(_id id)
		: Cache(id) {

}

void MSICache::read(_address address) {
	std::cout << "Read address MSI " << std::hex << address << "\n";
	CacheSet::CacheLine* line;
	if ((line = get_line(address)) != NULL) {
		//same as invalid state
	} else {
		switch (line->state) {
			case CacheSet::MODIFIED:
			case CacheSet::SHARED:
				//read the data
				break;
			case CacheSet::INVALID:
				//snoop and further operations
			default:
				//invalid state
				break;
		}
	}

}

void MSICache::write(_address address) {
	std::cout << "Write address MSI " << std::hex << address << "\n";
	CacheSet::CacheLine* line;
	_id set_id = get_set_id(address);
	if ((line = get_line(address)) == NULL) {
		sets[set_id]->add_line(address, CacheSet::SHARED);
	} else {
		switch (line->state) {
			case CacheSet::MODIFIED:
				//modfiy data
				break;
			case CacheSet::SHARED:
				//notify other caches
			case CacheSet::INVALID:
				//notify other caches
			default:
				//invalid state
				break;
		}
	}
}
