/*
 * FifoWriter.cpp
 */

#include <iostream>

#include "FifoWriter.h"

FifoWriter::FifoWriter(Vfifo* fifo, const std::vector<uint8_t>& values)
	: fifo(fifo), values(values)
{
	i = (this->values).begin();
}

void FifoWriter::evaluate()
{
	fifo->we = 0;
	if (!(int)(fifo->full))
	{
		fifo->we = 1;
		fifo->w_data = *i;
		std::cout << "Data Written: " << (int)*i << std::endl;
		i++;
	}
}