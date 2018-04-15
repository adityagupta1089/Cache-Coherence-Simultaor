#ifndef INCLUDE_SIMULATOR_HPP_
#define INCLUDE_SIMULATOR_HPP_

#include <vector>

#include "Cache.hpp"
#include "Constants.hpp"

enum _operation {
	READ = 'R',
	WRITE = 'W'
};

class Simulator {

	private:
		std::vector<Cache*> caches;
		Bus* bus;

	public:
		Simulator();
		void push_request(_operation, _address, _id);

};

#endif /* INCLUDE_SIMULATOR_HPP_ */
