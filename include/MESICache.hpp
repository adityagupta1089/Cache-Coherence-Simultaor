#ifndef INCLUDE_MESICACHE_H_
#define INCLUDE_MESICACHE_H_

#include "Cache.hpp"
#include "Constants.hpp"

class MESICache: public Cache {
	private:
		void read(_address address);
		void write(_address address);

	public:
		MESICache(_id id);
};

#endif /* INCLUDE_MESICACHE_H_ */
