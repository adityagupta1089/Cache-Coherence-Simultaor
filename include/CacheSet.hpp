#ifndef INCLUDE_CACHESET_HPP_
#define INCLUDE_CACHESET_HPP_

#include <vector>

#include "Constants.hpp"
#include "Simulator.hpp"

class CacheSet {
	public:
		enum line_state {
			MODIFIED = 'M',
			OWNED = 'O',
			EXCLUSIVE = 'E',
			SHARED = 'S',
			INVALID = 'I'
		};

		struct CacheLine {
				_address address;
				line_state state;

				CacheLine(_address paddress, line_state pstate)
						: address(paddress), state(pstate) {
				}

				void invalidate() {
					state = INVALID;
				}
		};

	private:
		std::vector<CacheLine*> lines;
		Simulator::Statistics& stats;

	public:
		CacheSet(Simulator::Statistics&);
		void add_line(_address, line_state);
		CacheLine* get_line(_address);
};

#endif /* INCLUDE_CACHESET_HPP_ */
