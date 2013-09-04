/***************************************************************************
 *  LasProcess.cpp
 *  2012- Florent Berthaut
 *  ANR INEDIT Project
 *  This file is part of libLAScore
 ****************************************************************************/

#include "LasProcess.hpp"

#include <iostream>
#include <stdexcept>

#include "LasScoreManager.hpp"
#include "LasChannel.hpp"
#include "LasInputBuffer.hpp"

using namespace std;

namespace lascore {

LasProcess::LasProcess():   m_positionInMs(1),
                            m_lengthInMs(1000),
                            m_triggered(false) {
    LasScoreManager* man = LasScoreManager::getInstance();
    m_id = man->getIscoreEngines()->addBox(m_positionInMs, 
                                                m_lengthInMs, 
                                                    ROOT_BOX_ID);
    DEBUG("Creating process "<<m_id);
    vector<unsigned int> vec;
/*
    m_relationID = man->getIscoreEngines()->addTemporalRelation(
                                        m_id, 
                                        BEGIN_CONTROL_POINT_INDEX, 
                                        man->getRootID(), 
                                        BEGIN_CONTROL_POINT_INDEX, 
                                        ANTPOST_ANTERIORITY, m_positionInMs, 
                                        NO_BOUND, vec);
*/
    DEBUG("Created process "<<m_id<<" with relation "<<m_relationID);
    testEditBox(m_positionInMs, m_lengthInMs);
}

LasProcess::~LasProcess() {}

void LasProcess::addChannel() {
    m_channels.push_back(new LasChannel());
    m_channels.back()->setProcess(this);
    m_channels.back()->setID(m_channels.size()-1);
}

void LasProcess::setPositionInMs(const uint64_t& pos) {
    if(pos>0) {
        testEditBox(pos, m_lengthInMs);
    }
}

void LasProcess::setLengthInMs(const uint64_t& length) {
    if(length>0) {
        testEditBox(m_positionInMs, length);
    }
}

AudioStreamPtr LasProcess::getStream(LasChannel* chan) {
    return chan->getInputStream();
}

void LasProcess::prepareStreamChannel(const unsigned int& streamChanID, 
                                                    LasInputBuffer* inpBuf, 
                                                            bool& triggered) {
    if(m_triggered) {
        triggered=true;
        m_streamChannelMap[streamChanID].push_back(inpBuf);
    }
    else {
        vector<LasChannel*>::iterator itChan = m_channels.begin();
        for(; itChan!=m_channels.end(); ++itChan) {
            vector<LasInputBuffer*>::const_iterator itBuf 
                                        = (*itChan)->getInputBuffers().begin();
            for(; itBuf!=(*itChan)->getInputBuffers().end() && !triggered; 
                                                                    ++itBuf) {
                (*itBuf)->prepareStreamChannel(streamChanID, 
                                                        (*itBuf), 
                                                            triggered);
            }
        }
    }
}

void LasProcess::testEditBox(const uint64_t& pos, const uint64_t& length) {
    try {
        LasScoreManager* man = LasScoreManager::getInstance();
        vector<unsigned int> vec;
        //man->getIscoreEngines()->changeTemporalRelationBounds(
        //                           m_relationID, pos, NO_BOUND, vec);
        bool done = man->getIscoreEngines()->performBoxEditing(m_id, 
                                                    pos, 
                                                    pos+length,
                                                    vec, 
                                                    NO_MAX_MODIFICATION);
        man->updateAllBoxes();
        if(!done) {
            DEBUG("Process "<<m_id
                    <<" could not be moved to "
                    <<pos<<" - "<<pos+length);
        }
    }
    catch(exception e) {
        DEBUG("Error when moving process "<<m_id<<" : "<<e.what());
    }
}

void LasProcess::updateBox() {
    LasScoreManager* man = LasScoreManager::getInstance();
    m_positionInMs=man->getIscoreEngines()->getBoxBeginTime(m_id);
    m_positionInFrames = man->msToFrames(m_positionInMs);
    m_lengthInMs=man->getIscoreEngines()->getBoxDuration(m_id);
    m_lengthInFrames = man->msToFrames(m_lengthInMs);
    DEBUG("Process "<<m_id<<" at absolute ms position "<<m_positionInMs);
}

void LasProcess::updateBoxes() {
    updateBox();
    vector<LasChannel*>::iterator itChan = m_channels.begin();
    for(; itChan!=m_channels.end(); ++itChan) {
        (*itChan)->updateBoxes();
    }
}

void LasProcess::start() {
    //get the current frame
    RendererInfo info;
    AudioPlayerPtr player = LasScoreManager::getInstance()->getLASPlayer();
    AudioRendererPtr renderer = GetAudioPlayerRenderer(player);
    GetAudioRendererInfo(renderer, &info);

    //build the streams for each channel
    map<unsigned int, vector<LasInputBuffer*> >::iterator itChan;
    for(itChan=m_streamChannelMap.begin(); 
                itChan!=m_streamChannelMap.end(); ++itChan) {
        AudioStreamPtr mixStream = MakeNullSoundPtr(0);
        vector<LasInputBuffer*>::iterator itBuf = itChan->second.begin();
        for(; itBuf!=itChan->second.end(); ++itBuf) {
            AudioStreamPtr sil = MakeNullSoundPtr((*itBuf)->getAbsPosInFrames()
                                                    - info.fCurFrame);
            mixStream = MakeMixSoundPtr(mixStream, 
                                        MakeSeqSoundPtr(sil, 
                                                        (*itBuf)->getStream(),
                                                        0));

            DEBUG("In Process "<<m_id<<" adding buffer at frame "
                            <<(*itBuf)->getAbsPosInFrames()-info.fCurFrame
                            <<" to LAS channel "<<itChan->first);
        }
        LoadChannelPtr(player, mixStream, itChan->first, 1.0f, 1.0f, 1.0f);
    }

    //start playing the LAS streams
    for(itChan=m_streamChannelMap.begin(); 
                itChan!=m_streamChannelMap.end(); ++itChan) {
        StartChannel(player, itChan->first);
        DEBUG("Starting LAS channel "<<itChan->first
                <<" at frame "<<info.fCurFrame);
    }
}

void LasProcess::stop() {
    //TODO ?
}

}

