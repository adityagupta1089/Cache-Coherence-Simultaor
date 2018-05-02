#ifndef INCLUDE_SIMULATOR_HPP_
#define INCLUDE_SIMULATOR_HPP_

#include <vector>

#include "Constants.hpp"

class Cache;
class Bus;

enum _operation {
	READ = 'R',
	WRITE = 'W'
};

class Simulator {

	public:
		struct Statistics {
				unsigned int flushes;
				unsigned int hits;
				unsigned int misses;
				unsigned int evicts;
				unsigned int shares;
				unsigned int bus_requests;
		};

	private:
		std::vector<Cache*> caches;
		Bus* bus;

		Statistics stats;

	public:
		Simulator();
		void push_request(_operation, _address, _id);
		void print_statistics();

};

#endif /* INCLUDE_SIMULATOR_HPP_ */
