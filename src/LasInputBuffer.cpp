/***************************************************************************
 *  LasInputBuffer.cpp
 *  2012- Florent Berthaut
 *  ANR INEDIT Project
 *  This file is part of libLASProc
 ****************************************************************************/

#include "LasInputBuffer.hpp"

#include "LasChannel.hpp"
#include "LasProcess.hpp"
#include "LasOutputBuffer.hpp"

using namespace std;

namespace lascore {

LasInputBuffer::LasInputBuffer(LasOutputBuffer* out):m_connectedBuffer(out),
                                                    m_positionInFrames(0) {}

LasInputBuffer::~LasInputBuffer() {}

AudioStreamPtr LasInputBuffer::getStream() {
/*
    AudioStreamPtr sil = MakeNullSoundPtr(m_positionInFrames);
    AudioStreamPtr conBufStream = m_connectedBuffer->getStream(0);
    return MakeSeqSoundPtr(sil, confBufStream, 0);
*/
    return m_connectedBuffer->getStream();
}

void LasInputBuffer::prepareStreamChannel(const unsigned int& streamChanID, 
                                            LasInputBuffer* inpBuf, 
                                            bool& triggered) {
    m_connectedBuffer->prepareStreamChannel(streamChanID, inpBuf, triggered);
}

uint64_t LasInputBuffer::getAbsPosInFrames() {
    return m_positionInFrames+m_channel->getProcess()->getPositionInFrames();
}

}

