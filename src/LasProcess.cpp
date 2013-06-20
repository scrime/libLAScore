/***************************************************************************
 *  LasProcess.cpp
 *  2012- Florent Berthaut
 *  ANR INEDIT Project
 *  This file is part of libLAScore
 ****************************************************************************/

#include <lascore/LasProcessesManager.hpp>
#include <lascore/LasProcess.hpp>
#include <lascore/LasChannel.hpp>


using namespace std;

LasProcess::LasProcess() {
    m_channels.push_back(new LasChannel(0));
    m_id = LasProcessesManager::getInstance()
                ->getIscoreEngines()->addBox(0, 1000, ROOT_BOX_ID);
}

LasProcess::~LasProcess() {}

void LasProcess::startChannels() {
/*
    //get the current frame
    RendererInfo info;
    AudioRendererPtr renderer = GetAudioPlayerRenderer(player);
    GetAudioRendererInfo(renderer, &info);

    //for each assigned channel
    //compute a stream of a PAR of all inputBuffers 
    //by giving them the current absolute position in the player 
    //load the stream into the channel and start processing the channel
*/
}

void LasProcess::setPositionMs(const unsigned long& pos) {
    m_positionMs=pos;
    updateBox();
}

void LasProcess::setLengthMs(const unsigned long& length) {
    m_lengthMs=length;
    updateBox();
}

void LasProcess::updateBox() {
    vector<unsigned int> vec;
	LasProcessesManager::getInstance()
        ->getIscoreEngines()->performBoxEditing(m_id, 
                                                m_positionMs, 
                                                m_lengthMs, 
                                                vec, 
                                                NO_MAX_MODIFICATION);
}

