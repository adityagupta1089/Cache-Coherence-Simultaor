#ifndef INCLUDE_MOESICACHE_HPP_
#define INCLUDE_MOESICACHE_HPP_

#include "Bus.hpp"
#include "Cache.hpp"
#include "Constants.hpp"

class MOESICache: public Cache {
	private:
		void read_request(_address);
		void write_request(_address);

	public:
		MOESICache(_id id, Bus* pbus);

		virtual bool handle_bus_request(Bus::BusRequest);
};

#endif /* INCLUDE_MOESICACHE_HPP_ */
