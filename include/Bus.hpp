#ifndef INCLUDE_BUS_HPP_
#define INCLUDE_BUS_HPP_

#include "Constants.hpp"

class Bus {

		enum bus_operation {
			read_miss,
			write_miss,
			read_hit,
			write_hit,
		//etc.
		};

		struct BusRequest {
				bus_operation operation;
				_address address;
		};
};

#endif /* INCLUDE_BUS_HPP_ */
