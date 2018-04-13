#ifndef INCLUDE_SIMULATOR_HPP_
#define INCLUDE_SIMULATOR_HPP_

#include <vector>

#include "Bus.hpp"
#include "Cache.hpp"
#include "Constants.hpp"

enum _operation {
	READ = 'R',
	WRITE = 'W'
};

class Simulator {

	private:
		std::vector<Cache*> caches;
		Bus bus;

	public:
		Simulator(protocol _protocol);
		void push_request(_operation operation, _address address, _id id);

};

#endif /* INCLUDE_SIMULATOR_HPP_ */
