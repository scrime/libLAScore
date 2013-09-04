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

#include "LasScoreManager.hpp"

using namespace std;

namespace lascore {

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
    LasOutputBuffer* outBuf = new LasOutputBuffer(this);
    m_outputBuffers.push_back(outBuf);
    LasScoreManager* man = LasScoreManager::getInstance();
    std::vector<unsigned int> movedBoxes;
    man->getIscoreEngines()->addTemporalRelation(
                                m_process->getID(), BEGIN_CONTROL_POINT_INDEX, 
                                outBuf->getID(), BEGIN_CONTROL_POINT_INDEX,
                                ANTPOST_ANTERIORITY, movedBoxes);
    man->getIscoreEngines()->addTemporalRelation(
                                outBuf->getID(), END_CONTROL_POINT_INDEX,
                                m_process->getID(), END_CONTROL_POINT_INDEX, 
                                ANTPOST_ANTERIORITY, movedBoxes);
    return outBuf;
}

LasInputBuffer* LasChannel::addInputBuffer(LasOutputBuffer* outBuf) {
    LasInputBuffer* inpBuf = new LasInputBuffer(this, outBuf);
    outBuf->connectBuffer(inpBuf);
    m_inputBuffers.push_back(inpBuf);
    LasScoreManager* man = LasScoreManager::getInstance();
    vector<unsigned int> vec;
    man->getIscoreEngines()->addTemporalRelation(
                                m_process->getID(), BEGIN_CONTROL_POINT_INDEX, 
                                inpBuf->getID(), BEGIN_CONTROL_POINT_INDEX,
                                ANTPOST_ANTERIORITY, vec);
    man->getIscoreEngines()->addTemporalRelation(
                                outBuf->getID(), END_CONTROL_POINT_INDEX,
                                m_process->getID(), END_CONTROL_POINT_INDEX, 
                                ANTPOST_ANTERIORITY, vec);
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

const uint64_t& LasChannel::getLengthInMs() { 
    return m_process->getLengthInMs();
}

void LasChannel::updateBoxes() {
    vector<LasInputBuffer*>::iterator itIBuf = m_inputBuffers.begin();
    for(; itIBuf!=m_inputBuffers.end(); ++itIBuf) {
        (*itIBuf)->updateBox();
    }
    vector<LasOutputBuffer*>::iterator itOBuf = m_outputBuffers.begin();
    for(; itOBuf!=m_outputBuffers.end(); ++itOBuf) {
        (*itOBuf)->updateBox();
    }
}

}

