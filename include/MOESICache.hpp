#ifndef INCLUDE_MOESICACHE_HPP_
#define INCLUDE_MOESICACHE_HPP_

#include "Bus.hpp"
#include "Cache.hpp"
#include "Constants.hpp"
#include "Simulator.hpp"

class MOESICache: public Cache {
	private:
		void read_request(_address);
		void write_request(_address);

	public:
		MOESICache(_id, Bus*, Simulator::Statistics&);

		virtual bool handle_bus_request(Bus::BusRequest);
};

#endif /* INCLUDE_MOESICACHE_HPP_ */
