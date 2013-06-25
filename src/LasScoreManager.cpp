/***************************************************************************
 *  LasScoreManager.cpp
 *  2012 Florent Berthaut
 *  ANR INEDIT Project
 *  This file is part of libLASProc
 ****************************************************************************/

#include "LasScoreManager.hpp"

#include <iostream>
#include <stdexcept>

#include "LasAudioInputProcess.hpp"
#include "LasAudioOutputProcess.hpp"
#include "LasFaustProcess.hpp"
#include "LasSoundfileProcess.hpp"

using namespace std;

void controlPointCallBack(  unsigned int boxId, 
                            unsigned int controlPointIndex, 
                            std::vector<unsigned int> processToStop) {
    LasScoreManager* man = LasScoreManager::getInstance();
    if(controlPointIndex == BEGIN_CONTROL_POINT_INDEX) {
        if(man->m_processesMap.find(boxId)!=man->m_processesMap.end()) {
            man->m_processesMap[boxId]->start();
        }
    } else {
        if(man->m_processesMap.find(boxId)!=man->m_processesMap.end()) {
            man->m_processesMap[boxId]->stop();
        }
    }
}

void waitedTriggerPointCallBack(bool isWaited, 
                                unsigned int triggerId, 
                                unsigned int boxId, 
                                unsigned int controlPointIndex, 
                                std::string triggerMessage) {
/*
	if(isWaited) {
		std::string controlPointPosition;
		if (controlPointIndex == BEGIN_CONTROL_POINT_INDEX) {
			controlPointPosition = "BOX BEGIN";
		} else {
			controlPointPosition = "BOX END";
		}

		std::cout << "* A Trigger Point is ready to be activated *" << std::endl;
		std::cout << "Please send the Trigger Point message ("<< triggerMessage << ") to this computer using the port 7002" << std::endl;
		std::cout << "(or quit by pressing ctrl-C)" << std::endl;
		std::cout << "<BoxID, ControlPoint Position, Trigger message>: <"
		<< boxId << ", " << controlPointPosition << ", " << triggerMessage
		<< ">" << std::endl;
	}
*/
}

void isExecutionFinishedCallBack() {
    LasScoreManager::getInstance()->stop();
}

LasScoreManager::LasScoreManager(): m_audioInputProc(NULL),
                                    m_audioOutputProc(NULL),
                                    m_inpChanNb(2),
                                    m_outChanNb(2), 
                                    m_playChanNb(10), 
                                    m_sampleRate(44100), 
                                    m_audioBufSize(512), 
                                    m_rtAudioBufSize(512), 
                                    m_fileBufSize(65536 * 4) {
    //create the IScore Engines
    m_engines = new Engines(60000);

    //define the IScore callbacks
    m_engines->addCrossingCtrlPointCallback(&controlPointCallBack);
    m_engines->addCrossingTrgPointCallback(&waitedTriggerPointCallBack);
    m_engines->addExecutionFinishedCallback(&isExecutionFinishedCallBack);

    //create the LAS audio player 
    m_player = OpenAudioPlayer(m_inpChanNb, m_outChanNb, m_playChanNb, 
                                m_sampleRate, m_audioBufSize, m_fileBufSize, 
                                m_rtAudioBufSize, kCoreAudioRenderer, 1);
    if(!m_player) {
        throw logic_error("Error opening the LAS player");
    }
}

LasScoreManager::~LasScoreManager() {
    delete m_engines;
    delete m_audioInputProc;
    delete m_audioOutputProc;
}

LasScoreManager* LasScoreManager::getInstance() {
    static LasScoreManager instance;
    return &instance;
} 

void LasScoreManager::clear() {

    //TODO erase all processes

}

void LasScoreManager::start() {
    m_playing=true;

    //prepare the streams
    m_audioOutputProc->prepareStreamChannels();

    //TODO start the audio player
	StartAudioPlayer(m_player);

    //start the iscore engine
    m_engines->play();
}

void LasScoreManager::stop() {
    m_playing=false;
	StopAudioPlayer(m_player);
}

LasAudioInputProcess* LasScoreManager::getAudioInputProcess() { 
    if(m_audioInputProc==NULL) {
        m_audioInputProc= new LasAudioInputProcess();
        m_processesMap[m_audioInputProc->getID()]=m_audioInputProc;
    }
    return m_audioInputProc;
}

LasAudioOutputProcess* LasScoreManager::getAudioOutputProcess() { 
    if(m_audioOutputProc==NULL) {
        m_audioOutputProc= new LasAudioOutputProcess();
        m_processesMap[m_audioOutputProc->getID()]=m_audioOutputProc;
    }
    return m_audioOutputProc;
}

LasFaustProcess* LasScoreManager::createFaustProcess() {
    LasFaustProcess* newProc = new LasFaustProcess();
    m_processes.push_back(newProc);    
    m_processesMap[newProc->getID()]=newProc;
    return newProc;
}

LasSoundfileProcess* LasScoreManager::createSoundfileProcess() {
    LasSoundfileProcess* newProc = new LasSoundfileProcess();
    m_processes.push_back(newProc);    
    m_processesMap[newProc->getID()]=newProc;
    return newProc;
}

void LasScoreManager::update() {

    //update all the processes

}

uint64_t LasScoreManager::msToFrames(const uint64_t& ms) {
    return double(ms)/1000.0*(double)m_sampleRate;
}

