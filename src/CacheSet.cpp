#include <CacheSet.hpp>

void CacheSet::add_line(_address address, line_state state) {
	if (lines.size() >= LINES_PER_SET) {
		lines.erase(lines.begin());
	}
	lines.push_back(new CacheLine(address, state));
}

CacheSet::CacheLine* CacheSet::get_line(_address address) {
	for (CacheSet::CacheLine* line : lines) {
		if (line->address == address) {
			return line;
		}
	}
	return nullptr;
}

