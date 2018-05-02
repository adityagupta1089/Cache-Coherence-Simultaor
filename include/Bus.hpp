#ifndef INCLUDE_BUS_HPP_
#define INCLUDE_BUS_HPP_

#include <vector>

#include "CacheSet.hpp"
#include "Constants.hpp"
#include "Simulator.hpp"

class Cache;

class Bus {
	private:
		std::vector<Cache*>& caches;
		Simulator::Statistics& stats;

	public:
		enum bus_operation {
			read_miss,
			write_miss,
			invalidate,
			share_data
		};

		struct BusRequest {
				_id cache_id;
				bus_operation operation;
				_address address;
				CacheSet::CacheLine* data;
		};

		Bus(std::vector<Cache*>&, Simulator::Statistics&);

		void push_request(BusRequest);
};

#endif /* INCLUDE_BUS_HPP_ */
