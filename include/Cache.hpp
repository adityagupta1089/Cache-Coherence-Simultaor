#ifndef INCLUDE_CACHE_H_
#define INCLUDE_CACHE_H_

#include <vector>

#include "CacheSet.hpp"
#include "Constants.hpp"

class Cache {
	private:
		_id id;
		std::vector<CacheSet> sets;

	public:
		Cache(_id id, protocol _protocol);

		void add_line(_address address);
		void remove_line(_address address);
		bool contains_line(_address address);

		virtual void read(_address) = 0;
		virtual void write(_address) = 0;

		virtual ~Cache() = 0;
};

#endif /* INCLUDE_CACHE_H_ */
