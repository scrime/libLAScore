/***************************************************************************
 *  LasAudioOutputProcess.cpp
 *  2012- Florent Berthaut
 *  ANR INEDIT Project
 *  This file is part of libLASProc
 ****************************************************************************/

#include "LasAudioOutputProcess.hpp"

#include <iostream>

#include "LasChannel.hpp"
#include "LasInputBuffer.hpp"

using namespace std;

namespace lascore {

LasAudioOutputProcess::LasAudioOutputProcess(): LasProcess() { 
    addChannel();
}

LasAudioOutputProcess::~LasAudioOutputProcess() {}

void LasAudioOutputProcess::addChannel() {
    LasProcess::addChannel();
}

void LasAudioOutputProcess::load(const std::string& fileStr) {

}

void LasAudioOutputProcess::prepareStreamChannels() {
    unsigned int streamChanID=1;
    vector<LasChannel*>::iterator itChan = m_channels.begin();
    for(; itChan!=m_channels.end(); ++itChan) {
        vector<LasInputBuffer*>::const_iterator itBuf 
                                    = (*itChan)->getInputBuffers().begin();
        for(; itBuf!=(*itChan)->getInputBuffers().end(); ++itBuf) {
            bool triggered=false;
            (*itBuf)->prepareStreamChannel(streamChanID, (*itBuf), triggered);
            if(!triggered) {
                DEBUG("Preparing stream channels in AudioOutputProcessuffer " 
                        <<" buffer started in AudioOutputProcess");
                m_streamChannelMap[0].push_back(*itBuf);
            }
            else {
                DEBUG("Preparing stream channels in AudioOutputProcessuffer " 
                        <<" buffer started in triggered Process"
                        <<" for las stream "<<streamChanID);
                streamChanID++;
            }
        }
    }
}

}

