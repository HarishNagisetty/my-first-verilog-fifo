/*
 * main.cpp
 */

#include <iostream>
#include <bitset>
#include <vector>

#include "Vfifo.h"
#include "Vfifo_fifo.h"
#include "verilated.h"
#include "FifoWriter.h"

namespace TBUtility
{
    void clockTick(Vfifo*);
    void printVals(Vfifo*);
}

int main(int argc, char** argv)
{
    Verilated::commandArgs(argc, argv);

    std::vector<uint8_t> dataVector;
    dataVector.push_back(91);
    dataVector.push_back(55);
    dataVector.push_back(82);
    dataVector.push_back(31);
    dataVector.push_back(47);
    dataVector.push_back(57);
    dataVector.push_back(82);
    dataVector.push_back(25);
    dataVector.push_back(39);
    dataVector.push_back(43);
    dataVector.push_back(57);
    dataVector.push_back(89);
    dataVector.push_back(91);
    Vfifo* top = new Vfifo;

    FifoWriter writer (top, dataVector);

    top->rst = 1;
    top->ce = 1;
    top->re = 0;
    TBUtility::clockTick(top);
    top->rst = 0;

    for (int i = 0; i < 10; ++i)
    {
        writer.evaluate();
        TBUtility::clockTick(top);
    }

    top->re = 1;
    top->we = 0;
    for (int i = 0; i < 2; ++i)
    {
        TBUtility::clockTick(top);
        std::cout << "Data Read: ";
        std::cout << (int)top->r_data << std::endl;
    }

    top->re = 0;
    for (int i = 0; i < 10; ++i)
    {
        writer.evaluate();
        TBUtility::clockTick(top);
    }

    top->re = 1;
    top->we = 0;
    for (int i = 0; i < 4; ++i)
    {
        TBUtility::clockTick(top);
        std::cout << "Data Read: ";
        std::cout << (int)top->r_data << std::endl;
    }

    top->re = 0;
    for (int i = 0; i < 10; ++i)
    {
        writer.evaluate();
        TBUtility::clockTick(top);
    }

    top->re = 1;
    top->we = 0;
    for (int i = 0; i < 4; ++i)
    {
        TBUtility::clockTick(top);
        std::cout << "Data Read: ";
        std::cout << (int)top->r_data << std::endl;
    }

    top->final();
    delete top;

    exit(EXIT_SUCCESS);
}

/* function definitions */

void TBUtility::clockTick(Vfifo* top)
{
    top->clk = 0;
    top->eval();
    top->clk = 1;
    top->eval();
}

void TBUtility::printVals(Vfifo* top)
{
    int value = 0;
    std::cout << std::bitset<8> (value) << std::endl;
}