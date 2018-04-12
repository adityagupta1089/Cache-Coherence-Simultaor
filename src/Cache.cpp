#include <Constants.hpp>
#include <MESICache.hpp>
#include <MOESICache.hpp>
#include <MSICache.hpp>
#include "Cache.hpp"

Cache::Cache(_id pid, protocol pprotocol)
		: id(pid) {
	/*switch (pprotocol) {
		case MSI:
			*this = MSICache();
			break;
		case MESI:
			*this = MESICache();
			break;
		case MOESI:
			*this = MOESICache();
			break;
	}*/
}
