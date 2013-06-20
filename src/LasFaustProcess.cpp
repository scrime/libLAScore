/***************************************************************************
 *  LasFaustProcess.cpp
 *  2012- Florent Berthaut
 *  ANR INEDIT Project
 *  This file is part of libLASProc
 ****************************************************************************/

#include <lascore/LasFaustProcess.hpp>

using namespace std;

LasFaustProcess::LasFaustProcess():LasProcess() {}

LasFaustProcess::~LasFaustProcess() {}

/*
AudioStreamPtr LasFaustProcess::getStream() {
    //combine the input channel with ID with the corresponding faust process
    return MakeTransformSoundPtr(m_channel[]->getStream(), m_effectList, 0, 0);
}
*/

void LasFaustProcess::addChannel() {
/*
    m_channels.push_back(new LasChannel());
    m_effectLists.push_back(MakeAudioEffectListPtr());
    setFaustEffect(m_effectStr);
*/
}

void LasFaustProcess::load(const std::string& effectStr) {
    m_effectStr=effectStr;
/*
    for(unsigned int c=0; c<m_channels.size(); ++c) {
        ClearAudioEffectListPtr(m_effectLists[c]);
        AddAudioEffectPtr(m_effectLists[c], 
                            MakeFaustAudioEffectPtr(effectStr.c_str()));
    }
*/
}


