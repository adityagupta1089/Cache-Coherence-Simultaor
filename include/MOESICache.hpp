#ifndef INCLUDE_MOESICACHE_H_
#define INCLUDE_MOESICACHE_H_

#include "Cache.hpp"

class MOESICache: public Cache {
			private:
		void read(_address address);
		void write(_address address);
	public:
		MOESICache(_id id);
};

#endif /* INCLUDE_MOESICACHE_H_ */
