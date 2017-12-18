#ifndef CYCLIC_BUFFER_H
#define CYCLIC_BUFFER_H

#include <stdint.h>

#define SIZE 4096

struct buffer_t
{
	volatile uint64_t data[SIZE];
	volatile uint64_t pos;
};
#endif