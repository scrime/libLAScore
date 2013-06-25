/***************************************************************************
 *  LasChannel.cpp
 *  2012- Florent Berthaut
 *  ANR INEDIT Project
 *  This file is part of libLASProc
 ****************************************************************************/

#include "LasChannel.hpp"

#include "LasOutputBuffer.hpp"
#include "LasInputBuffer.hpp"
#include "LasProcess.hpp"

using namespace std;

LasChannel::LasChannel() {}

LasChannel::~LasChannel() {}

AudioStreamPtr LasChannel::getInputStream() {
    AudioStreamPtr mixStream = MakeNullSoundPtr(0);
    vector<LasInputBuffer*>::iterator itBuf = m_inputBuffers.begin();
    for(; itBuf!=m_inputBuffers.end(); ++itBuf) {
        AudioStreamPtr sil = MakeNullSoundPtr((*itBuf)->getPositionInFrames());
        mixStream = MakeMixSoundPtr(mixStream, 
                                    MakeSeqSoundPtr(sil, 
                                                    (*itBuf)->getStream(),
                                                    0));
    }
    return mixStream;
}

AudioStreamPtr LasChannel::getOutputStream() {
    return m_process->getStream(this);
}

LasOutputBuffer* LasChannel::addOutputBuffer() {
    LasOutputBuffer* outBuf = new LasOutputBuffer();
    outBuf->setChannel(this);
    m_outputBuffers.push_back(outBuf);
    return outBuf;
}

LasInputBuffer* LasChannel::addInputBuffer(LasOutputBuffer* outBuf) {
    LasInputBuffer* inpBuf = new LasInputBuffer(outBuf);
    inpBuf->setChannel(this);
    outBuf->connectBuffer(inpBuf);
    m_inputBuffers.push_back(inpBuf);
    return inpBuf;
}

void LasChannel::prepareStreamChannel(const unsigned int& streamChanID, 
                                        LasInputBuffer* inpBuf, 
                                        bool& triggered) {
    m_process->prepareStreamChannel(streamChanID, inpBuf, triggered);
}

const uint64_t& LasChannel::getLengthInFrames() { 
    return m_process->getLengthInFrames();
}
