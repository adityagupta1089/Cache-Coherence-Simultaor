#include <CacheSet.hpp>

CacheSet::CacheSet() {
	lines = new CacheLine*[LINES_PER_SET];
}

void CacheSet::add_line(_address address, line_state state) {
	for (unsigned i = 0; i < LINES_PER_SET; i++) {
		if (!lines[i]) {
			lines[i] = new CacheLine(address, state);
			return;
		}
	}
	// TODO evict a line
}

void CacheSet::remove_line(_address address) {
	// TODO
}

CacheSet::CacheLine* CacheSet::get_line(_address address) {
	for (unsigned i = 0; i < LINES_PER_SET; i++) {
		CacheLine* line = lines[i];
		if (line && line->address == address) {
			return line;
		}
	}
	return nullptr;
}

