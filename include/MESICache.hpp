#ifndef INCLUDE_MESICACHE_HPP_
#define INCLUDE_MESICACHE_HPP_

#include "Bus.hpp"
#include "Cache.hpp"
#include "Constants.hpp"

class MESICache: public Cache {
	private:
		void read_request(_address);
		void write_request(_address);

	public:
		MESICache(_id id, Bus* pbus);

		virtual bool handle_bus_request(Bus::BusRequest);
};

#endif /* INCLUDE_MESICACHE_HPP_ */
