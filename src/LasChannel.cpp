/***************************************************************************
 *  LasChannel.cpp
 *  2012- Florent Berthaut
 *  ANR INEDIT Project
 *  This file is part of libLASProc
 ****************************************************************************/

#include <lascore/LasChannel.hpp>
#include <lascore/LasOutputBuffer.hpp>
#include <lascore/LasInputBuffer.hpp>

using namespace std;

LasChannel::LasChannel(const unsigned int& id) {}

LasChannel::~LasChannel() {}

/*
AudioStreamPtr LasChannel::getStream() {
    //par 
    //of all inputBuffers
}
*/

LasOutputBuffer* LasChannel::addOutputBuffer() {
    LasOutputBuffer* outBuf = new LasOutputBuffer();
    m_outputBuffers.push_back(outBuf);
    return outBuf;
}

LasInputBuffer* LasChannel::addInputBuffer(LasOutputBuffer* outBuf) {
    LasInputBuffer* inpBuf = new LasInputBuffer(outBuf);
    outBuf->connectBuffer(inpBuf);
    m_inputBuffers.push_back(inpBuf);
    return inpBuf;
}

