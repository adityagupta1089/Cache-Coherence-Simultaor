#ifndef INCLUDE_CACHE_H_
#define INCLUDE_CACHE_H_

#include <vector>

#include "Bus.hpp"
#include "CacheSet.hpp"
#include "Constants.hpp"

class Bus;

class Cache {
	protected:
		_id id;
		std::vector<CacheSet*> sets;
		Bus* bus;

		bool require_share_data;

		void add_line(_address);
		void remove_line(_address);

		CacheSet::CacheLine* get_line(_address);

		_id get_set_id(_address);

	public:
		Cache(_id id, Bus* pbus);

		bool push_bus_request(Bus::BusRequest);

		virtual void read_request(_address) = 0;
		virtual void write_request(_address) = 0;
		virtual bool handle_bus_request(Bus::BusRequest) = 0;

		virtual ~Cache() {
		}
};

#endif /* INCLUDE_CACHE_H_ */
