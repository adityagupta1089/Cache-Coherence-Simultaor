#ifndef INCLUDE_CACHE_H_
#define INCLUDE_CACHE_H_

#include <vector>

#include "CacheSet.hpp"
#include "Constants.hpp"

class Cache {
	private:
		_id id;
		std::vector<CacheSet> sets;

		void add_line(_address address);
		void remove_line(_address address);
		bool contains_line(_address address);

	public:
		Cache(_id id);

		virtual void read(_address) = 0;
		virtual void write(_address) = 0;

		virtual ~Cache() {
		}
};

#endif /* INCLUDE_CACHE_H_ */
