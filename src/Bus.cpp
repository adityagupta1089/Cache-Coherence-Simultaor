#include <Bus.hpp>

Bus::Bus(std::vector<Cache*>& pcaches)
		: caches(pcaches) {

}

void Bus::push_request(BusRequest request) {
	/*
	 * TODO Handle bus requests, is broadcasting this request back to all
	 * caches OK?
	 */
}
