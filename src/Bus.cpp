#include <Bus.hpp>
#include <Cache.hpp>

Bus::Bus(std::vector<Cache*>& pcaches, Simulator::Statistics& pstats)
		: caches(pcaches), stats(pstats) {

}

void Bus::push_request(BusRequest request) {
	stats.bus_requests++;
	if (request.operation == Bus::share_data) stats.shares++;
	for (Cache* cache : caches) {
		if (cache->push_bus_request(request)) break;
	}
}
