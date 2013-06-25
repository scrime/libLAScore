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

LasAudioOutputProcess::LasAudioOutputProcess(): LasProcess() { 
    addChannel();
}

LasAudioOutputProcess::~LasAudioOutputProcess() {}

void LasAudioOutputProcess::addChannel() {
    LasProcess::addChannel();
    //m_channels.push_back(new LasChannel());
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
                cout<<"buffer in outputproc"<<endl;
                m_streamChannelMap[0].push_back(*itBuf);
            }
            else {
                cout<<"buffer in triggered proc"<<endl;
                streamChanID++;
            }
        }
    }
}

