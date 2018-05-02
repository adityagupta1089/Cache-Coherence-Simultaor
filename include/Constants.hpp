#ifndef INCLUDE_CONSTANTS_HPP_
#define INCLUDE_CONSTANTS_HPP_

typedef unsigned long long _address;
typedef unsigned int _id;
typedef unsigned int _cycle;

enum protocol {
	MSI,
	MESI,
	MOESI
};

const unsigned int PROCESSORS = 4;
const unsigned int SETS = 64;
const unsigned int LINES_PER_SET = 8;
const unsigned int BYTES_PER_LINE = 64;

const unsigned int ADDRESS_BITS = 32;
const unsigned long MEMORY_SIZE = 1LL << ADDRESS_BITS;
const unsigned int OFFSET_BITS = 6;
const unsigned int INDEX_BITS = 6;
const unsigned int TAG_BITS = 20;

const protocol PROTOCOL = MOESI;

#endif /* INCLUDE_CONSTANTS_HPP_ */
