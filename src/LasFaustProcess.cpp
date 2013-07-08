/***************************************************************************
 *  LasFaustProcess.cpp
 *  2012- Florent Berthaut
 *  ANR INEDIT Project
 *  This file is part of libLAScore
 ****************************************************************************/

#include "LasFaustProcess.hpp"

#include <iostream>
#include <stdexcept>

#include "LasChannel.hpp"

using namespace std;

namespace lascore {

LasFaustProcess::LasFaustProcess(): LasProcess() {
    addChannel();
}

LasFaustProcess::~LasFaustProcess() {}

AudioStreamPtr LasFaustProcess::getStream(LasChannel* chan) {
    return MakeTransformSoundPtr(chan->getInputStream(), 
                                    m_effectLists[chan->getID()], 0, 0);
}

void LasFaustProcess::addChannel() {
    LasProcess::addChannel();
    m_effectLists.push_back(MakeAudioEffectListPtr());
    if(m_effectStr.compare("")!=0) {
        load(m_effectStr);
    }
}

void LasFaustProcess::load(const std::string& effectStr) {
    m_effectStr=effectStr;
    try{
        for(unsigned int c=0; c<m_effectLists.size(); ++c) {
            ClearAudioEffectListPtr(m_effectLists[c]);
            AudioEffectPtr fx = 
                MakeFaustAudioEffectPtr(m_effectStr.c_str(), "", "");
            AddAudioEffectPtr(m_effectLists[c], fx);
        }
    }
    catch(exception e) {
        cout<<"Error when loading the faust effect "<<effectStr
            <<" : "<<e.what()<<endl;
    }
}

}

