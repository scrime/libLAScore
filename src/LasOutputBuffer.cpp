/***************************************************************************
 *  LasOutputBuffer.cpp
 *  2012- Florent Berthaut
 *  ANR INEDIT Project
 *  This file is part of libLASProc
 ****************************************************************************/

#include <lascore/LasOutputBuffer.hpp>

using namespace std;

LasOutputBuffer::LasOutputBuffer() {}

LasOutputBuffer::~LasOutputBuffer() {}

void LasOutputBuffer::connectBuffer(LasInputBuffer* inpBuf) {
    m_connectedBuffers.push_back(inpBuf);
}

