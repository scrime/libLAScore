/***************************************************************************
 *  LasInputBuffer.cpp
 *  2012- Florent Berthaut
 *  ANR INEDIT Project
 *  This file is part of libLASProc
 ****************************************************************************/

#include <lascore/LasInputBuffer.hpp>
#include <lascore/LasOutputBuffer.hpp>

using namespace std;

LasInputBuffer::LasInputBuffer(LasOutputBuffer* out):m_connectedBuffer(out) {}

LasInputBuffer::~LasInputBuffer() {}

/*
AudioStreamPtr LasInputBuffer::getStream() {
    //sequence of 
    ////silence with size = (connectedBuffer absolute pos minus absolute pos)
    ////cut of process.channel content from (connectedBuffer absolute pos to abspos+size)
}
*/

