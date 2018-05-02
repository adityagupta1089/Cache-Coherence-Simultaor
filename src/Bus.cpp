#include <Bus.hpp>
#include <Cache.hpp>

Bus::Bus(std::vector<Cache*>& pcaches)
		: caches(pcaches) {

}

void Bus::push_request(BusRequest request) {
	for (Cache* cache : caches) {
		if (cache->push_bus_request(request)) break;
	}
}
