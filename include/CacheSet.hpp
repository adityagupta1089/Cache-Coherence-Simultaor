#ifndef INCLUDE_CACHESET_HPP_
#define INCLUDE_CACHESET_HPP_

#include <vector>

#include "Constants.hpp"

class CacheSet {
	private:
		friend class Cache;
		struct CacheLine {
				_address address;
				//etc
		};
		std::vector<CacheLine> lines;
	public:
		void add_line(_address address);
		void remove_line(_address address);
		bool contains_line(_address address);

		bool empty();
		int size();
};

#endif /* INCLUDE_CACHESET_HPP_ */
