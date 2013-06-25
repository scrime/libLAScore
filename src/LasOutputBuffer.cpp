/***************************************************************************
 *  LasOutputBuffer.cpp
 *  2012- Florent Berthaut
 *  ANR INEDIT Project
 *  This file is part of libLASProc
 ****************************************************************************/

#include "LasOutputBuffer.hpp"

#include "LasChannel.hpp"

using namespace std;

LasOutputBuffer::LasOutputBuffer():m_positionInFrames(0), 
                                    m_lengthInFrames(1000) {}

LasOutputBuffer::~LasOutputBuffer() {}

void LasOutputBuffer::connectBuffer(LasInputBuffer* inpBuf) {
    m_connectedBuffers.push_back(inpBuf);
}

void LasOutputBuffer::prepareStreamChannel(const unsigned int& streamChanID, 
                                            LasInputBuffer* inpBuf, 
                                            bool& triggered) {
    m_channel->prepareStreamChannel(streamChanID, inpBuf, triggered);
}

AudioStreamPtr LasOutputBuffer::getStream() {
   return MakeCutSoundPtr(m_channel->getOutputStream(), 
                            m_positionInFrames,
                                m_positionInFrames+m_lengthInFrames);
}

void LasOutputBuffer::setChannel(LasChannel* chan){
    m_channel=chan;
    m_positionInFrames=0;
    m_lengthInFrames=m_channel->getLengthInFrames();
}
