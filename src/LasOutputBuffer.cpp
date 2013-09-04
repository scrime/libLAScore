/***************************************************************************
 *  LasOutputBuffer.cpp
 *  2012- Florent Berthaut
 *  ANR INEDIT Project
 *  This file is part of libLASProc
 ****************************************************************************/

#include "LasOutputBuffer.hpp"

#include <iostream>

#include "LasProcess.hpp"
#include "LasChannel.hpp"
#include "LasScoreManager.hpp"
#include "LasInputBuffer.hpp"

using namespace std;

namespace lascore {

LasOutputBuffer::LasOutputBuffer(LasChannel* chan): m_channel(chan) {
    LasScoreManager* man = LasScoreManager::getInstance();
    m_id = man->getIscoreEngines()->addBox(
                                    m_channel->getProcess()->getPositionInMs(), 
                                    m_channel->getProcess()->getLengthInMs(),
                                    ROOT_BOX_ID);
    vector<unsigned int> movedBoxes;
    man->getIscoreEngines()->addTemporalRelation(
                                    m_channel->getProcess()->getID(), 
                                    BEGIN_CONTROL_POINT_INDEX, 
                                    m_id, 
                                    BEGIN_CONTROL_POINT_INDEX,
                                    ANTPOST_ANTERIORITY, movedBoxes);
    updateBox();
    DEBUG("Added output buffer with ID "<<m_id
            <<" to process "<<m_channel->getProcess()->getID());
}

LasOutputBuffer::~LasOutputBuffer() {}

void LasOutputBuffer::connectBuffer(LasInputBuffer* inpBuf) {
    m_connectedBuffers.push_back(inpBuf);
    LasScoreManager* man = LasScoreManager::getInstance();
    vector<unsigned int> movedBoxes;
    man->getIscoreEngines()->addTemporalRelation(
                                    m_id, BEGIN_CONTROL_POINT_INDEX,
                                    inpBuf->getID(), BEGIN_CONTROL_POINT_INDEX, 
                                    ANTPOST_ANTERIORITY, movedBoxes);
    man->updateAllBoxes();
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

const uint64_t& LasOutputBuffer::getPositionInFrames() {
    updateBox();
    return m_positionInFrames;
}

const uint64_t& LasOutputBuffer::getLengthInFrames() {
    updateBox();
    return m_lengthInFrames;
}

const uint64_t& LasOutputBuffer::getPositionInMs() {
    updateBox();
    return m_positionInMs;
}

const uint64_t& LasOutputBuffer::getAbsolutePositionInMs() {
    updateBox();
    return m_absolutePositionInMs;
}

const uint64_t& LasOutputBuffer::getLengthInMs() {
    updateBox();
    return m_lengthInMs;
}

void LasOutputBuffer::testEditBox(const uint64_t& pos, const uint64_t& length) {
    uint64_t absPos=pos+m_channel->getProcess()->getPositionInMs();
    LasScoreManager* man = LasScoreManager::getInstance();
    vector<unsigned int> vec;
    man->getIscoreEngines()->performBoxEditing( m_id, 
                                                absPos, 
                                                absPos+length,
                                                vec, 
                                                NO_MAX_MODIFICATION);
    updateBox();
}

void LasOutputBuffer::updateBox() {
    LasScoreManager* man = LasScoreManager::getInstance();
    m_absolutePositionInMs=man->getIscoreEngines()->getBoxBeginTime(m_id);
    DEBUG("Output buffer "<<m_id<<" at absolute ms position "
                                <<m_absolutePositionInMs);
    m_positionInMs=m_absolutePositionInMs
                    - m_channel->getProcess()->getPositionInMs();
    m_positionInFrames = man->msToFrames(m_positionInMs);
    m_lengthInMs=man->getIscoreEngines()->getBoxDuration(m_id);
    m_lengthInFrames = man->msToFrames(m_lengthInMs);
}

}

