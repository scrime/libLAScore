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

LasProcess::LasProcess():   m_positionInMs(0),
                            m_lengthInMs(1000),
                            m_triggered(false) {

    LasScoreManager* man = LasScoreManager::getInstance();
    m_positionInFrames = man->msToFrames(m_positionInMs);
    m_lengthInFrames = man->msToFrames(m_lengthInMs);

    m_id = man->getIscoreEngines()->addBox(m_positionInMs, 
                                                m_lengthInMs, 
                                                    ROOT_BOX_ID);
}

LasProcess::~LasProcess() {}

void LasProcess::addChannel() {
    m_channels.push_back(new LasChannel());
    m_channels.back()->setProcess(this);
    m_channels.back()->setID(m_channels.size()-1);
}

void LasProcess::setPositionInMs(const uint64_t& pos) {
    m_positionInMs=pos;
    m_positionInFrames = 
        LasScoreManager::getInstance()->msToFrames(m_positionInMs);
    updateBox();
}

void LasProcess::setLengthInMs(const uint64_t& length) {
    m_lengthInMs=length;
    m_lengthInFrames = LasScoreManager::getInstance()->msToFrames(m_lengthInMs);
    updateBox();
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

void LasProcess::updateBox() {
    try {
        LasScoreManager* man = LasScoreManager::getInstance();
        vector<unsigned int> vec;
        bool done = man->getIscoreEngines()->performBoxEditing(m_id, 
                                                    m_positionInMs, 
                                                    m_positionInMs+m_lengthInMs,
                                                    vec, 
                                                    NO_MAX_MODIFICATION);
        if(!done) {
            cout<<"Process "<<m_id
                <<" could not be moved to "
                <<m_positionInMs<<" - "<<m_positionInMs+m_lengthInMs<<endl;
        }
    }
    catch(exception e) {
        cout<<"Error when moving process "<<m_id<<" : "<<e.what()<<endl;
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
        }
        LoadChannelPtr(player, mixStream, itChan->first, 1.0f, 1.0f, 1.0f);
    }

    //start playing the LAS streams
    for(itChan=m_streamChannelMap.begin(); 
                itChan!=m_streamChannelMap.end(); ++itChan) {
        cout<<"Starting LAS channel "<<itChan->first
            <<" at frame "<<info.fCurFrame<<endl;
        StartChannel(player, itChan->first);
    }
}

void LasProcess::stop() {

}

