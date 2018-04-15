#include <CacheSet.hpp>

CacheSet::CacheSet() {
	lines.resize(LINES_PER_SET);
}

void CacheSet::add_line(_address address, line_state state) {
	if (lines.size() >= LINES_PER_SET) {
		lines.erase(lines.begin());
	}
	lines.push_back(new CacheLine(address, state));
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

