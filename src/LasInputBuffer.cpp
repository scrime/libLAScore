/***************************************************************************
 *  LasInputBuffer.cpp
 *  2012- Florent Berthaut
 *  ANR INEDIT Project
 *  This file is part of libLASProc
 ****************************************************************************/

#include "LasInputBuffer.hpp"

#include <iostream>

#include "LasChannel.hpp"
#include "LasProcess.hpp"
#include "LasOutputBuffer.hpp"

#include "LasScoreManager.hpp"

using namespace std;

namespace lascore {

LasInputBuffer::LasInputBuffer(LasChannel* chan, LasOutputBuffer* out):
                                                        m_channel(chan),
                                                        m_connectedBuffer(out),
                                                        m_positionInMs(1) {
    LasScoreManager* man = LasScoreManager::getInstance();
    m_positionInMs =  0;
    if(m_connectedBuffer->getAbsolutePositionInMs()>m_positionInMs) {
        m_positionInMs=m_connectedBuffer->getAbsolutePositionInMs() 
                        -m_channel->getProcess()->getPositionInMs();
    }
    m_id = man->getIscoreEngines()->addBox(
                                m_positionInMs+
                                    m_channel->getProcess()->getPositionInMs(), 
                                m_connectedBuffer->getLengthInMs(), 
                                ROOT_BOX_ID);
    vector<unsigned int> movedBoxes;
    man->getIscoreEngines()->addTemporalRelation(
                                    m_channel->getProcess()->getID(), 
                                    BEGIN_CONTROL_POINT_INDEX, 
                                    m_id, 
                                    BEGIN_CONTROL_POINT_INDEX,
                                    ANTPOST_ANTERIORITY, movedBoxes);
    editBox();
    DEBUG("Added input buffer with ID "<<m_id
            <<" to process "<<m_channel->getProcess()->getID());
}

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
    updateBox();
    return m_positionInFrames+m_channel->getProcess()->getPositionInFrames();
}

uint64_t LasInputBuffer::getPositionInFrames() {
    updateBox();
    return m_positionInFrames;
}

void LasInputBuffer::editBox() {
    m_positionInMs+=m_channel->getProcess()->getPositionInMs();
    LasScoreManager* man = LasScoreManager::getInstance();
    vector<unsigned int> vec;
    man->getIscoreEngines()->performBoxEditing(
                            m_id, 
                            m_positionInMs, 
                            m_positionInMs+m_connectedBuffer->getLengthInMs(),
                            vec, 
                            NO_MAX_MODIFICATION);
    updateBox();
}

void LasInputBuffer::updateBox() {
    LasScoreManager* man = LasScoreManager::getInstance();
    m_positionInMs=man->getIscoreEngines()->getBoxBeginTime(m_id);
    DEBUG("Input buffer "<<m_id<<" at absolute ms position "<<m_positionInMs);
    m_positionInMs-=m_channel->getProcess()->getPositionInMs();
    m_positionInFrames = man->msToFrames(m_positionInMs);
}

}

