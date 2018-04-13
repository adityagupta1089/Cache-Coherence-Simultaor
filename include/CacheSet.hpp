#ifndef INCLUDE_CACHESET_HPP_
#define INCLUDE_CACHESET_HPP_

#include "Constants.hpp"

class CacheSet {
	public:
		enum line_state {
			MODIFIED,
			OWNED,
			EXCLUSIVE,
			SHARED,
			INVALID
		};

		struct CacheLine {
				_address address;
				line_state state;
				CacheLine(_address paddress, line_state pstate)
						: address(paddress), state(pstate) {
				}
		};

	private:
		CacheLine** lines;

	public:
		CacheSet();

		void add_line(_address address, line_state state);
		void remove_line(_address address);
		CacheLine* get_line(_address address);

		bool empty() {
			// TODO
		}

		unsigned int size() {
			// TODO
		}
};

#endif /* INCLUDE_CACHESET_HPP_ */
