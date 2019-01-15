/*
 * Writer.h
 */

#ifndef WRITER_H 
#define WRITER_H

#include <vector>
#include <cstdint>

#include "Vfifo.h"

class FifoWriter
{
private:
	Vfifo* fifo;
	const std::vector<uint8_t>& values;
	std::vector<uint8_t>::const_iterator i;

public:
	FifoWriter(Vfifo* fifo, const std::vector<uint8_t>& values);
	void evaluate();
};

#endif