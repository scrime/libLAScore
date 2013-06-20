/***************************************************************************
 *  LasSoundfileProcess.cpp
 *  2012- Florent Berthaut
 *  ANR INEDIT Project
 *  This file is part of libLASProc
 ****************************************************************************/

#include <lascore/LasSoundfileProcess.hpp>

using namespace std;

LasSoundfileProcess::LasSoundfileProcess(): LasProcess() {}

LasSoundfileProcess::~LasSoundfileProcess() {}

/*
AudioStreamPtr LasSoundfileProcess::getStream() {
    //combine the input channel with ID with the corresponding faust process
    return MakeTransformSoundPtr(m_channel[]->getStream(), m_effectList, 0, 0);
}
*/

void LasSoundfileProcess::addChannel() {
/*
    m_channels.push_back(new LasChannel());
    m_effectLists.push_back(MakeAudioEffectListPtr());
    setSoundfileEffect(m_effectStr);
*/
}

void LasSoundfileProcess::load(const std::string& fileStr) {
/*
    m_effectStr=effectStr;
    for(unsigned int c=0; c<m_channels.size(); ++c) {
        ClearAudioEffectListPtr(m_effectLists[c]);
        AddAudioEffectPtr(m_effectLists[c], 
                            MakeSoundfileAudioEffectPtr(effectStr.c_str()));
    }
*/
}


