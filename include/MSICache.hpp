#ifndef INCLUDE_MSICACHE_H_
#define INCLUDE_MSICACHE_H_

#include "Cache.hpp"
#include "Constants.hpp"

class MSICache: public Cache {
	private:
		void read(_address address);
		void write(_address address);
	public:
		MSICache(_id id);
};

#endif /* INCLUDE_MSICACHE_H_ */
