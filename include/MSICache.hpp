#ifndef INCLUDE_MSICACHE_H_
#define INCLUDE_MSICACHE_H_

#include "Bus.hpp"
#include "Cache.hpp"
#include "Constants.hpp"

class MSICache: public Cache {
	private:
		void push_read_request(_address);
		void push_write_request(_address);

	public:
		MSICache(_id id, Bus* pbus);

		virtual void handle_bus_request(Bus::BusRequest);
};

#endif /* INCLUDE_MSICACHE_H_ */
