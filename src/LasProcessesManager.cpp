/***************************************************************************
 *  LasProcessesManager.cpp
 *  2012 Florent Berthaut
 *  ANR INEDIT Project
 *  This file is part of libLASProc
 ****************************************************************************/

#include <lascore/LasProcessesManager.hpp>

#include <iostream>
#include <stdexcept>

#include <lascore/LasAudioInputProcess.hpp>
#include <lascore/LasAudioOutputProcess.hpp>
#include <lascore/LasFaustProcess.hpp>
#include <lascore/LasSoundfileProcess.hpp>

using namespace std;

void controlPointCallBack(  unsigned int boxId, 
                            unsigned int controlPointIndex, 
                            std::vector<unsigned int> processToStop) {
    std::string controlPointPosition;
    if(controlPointIndex == BEGIN_CONTROL_POINT_INDEX) {
        controlPointPosition = "BOX BEGIN";
        //TODO, call start on the corresponding process
    } else {
        controlPointPosition = "BOX END";
        //TODO, call stop on the corresponding process
    }
    std::cout << "* A Control Point was just crossed *" << std::endl;
    std::cout << "<BoxID, ControlPoint position>: <"
        << boxId << ", " << controlPointPosition
        << ">" << std::endl;
}

void waitedTriggerPointCallBack(bool isWaited, 
                                unsigned int triggerId, 
                                unsigned int boxId, 
                                unsigned int controlPointIndex, 
                                std::string triggerMessage) {
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
}

void isExecutionFinishedCallBack() {
  std::cout << "* The execution is now finished *" << std::endl;
}


LasProcessesManager::LasProcessesManager(): m_inpChanNb(2),
                                            m_outChanNb(2), 
                                            m_playChanNb(10), 
                                            m_sampleRate(44100), 
                                            m_audioBufSize(512), 
                                            m_rtAudioBufSize(512), 
                                            m_fileBufSize(65536 * 4) {
    //create the IScore Engines
    m_engines = new Engines();

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
	StartAudioPlayer(m_player);

    //create the audio input and output processes
    m_audioInputProc=new LasInputBuffer

}

LasProcessesManager::~LasProcessesManager() {
    delete m_engines;
    delete m_audioInputProc;
    delete m_audioOutputProc;
}

LasProcessesManager* LasProcessesManager::getInstance() {
    static LasProcessesManager instance;
    return &instance;
} 

void LasProcessesManager::clear() {

    //TODO erase all processes

}

void LasProcessesManager::start() {
    m_playing=true;
    //TODO start iscore and the LAS player 

}

void LasProcessesManager::stop() {
    m_playing=false;
    //TODO stop iscore and the LAS player

}

LasFaustProcess* LasProcessesManager::createFaustProcess() {
    LasFaustProcess* newProc = new LasFaustProcess();
    m_processes.push_back(newProc);    
    m_processesMap[newProc->getID()]=newProc;
    return newProc;
}

LasSoundfileProcess* LasProcessesManager::createSoundfileProcess() {
    LasSoundfileProcess* newProc = new LasSoundfileProcess();
    m_processes.push_back(newProc);    
    m_processesMap[newProc->getID()]=newProc;
    return newProc;
}


void LasProcessesManager::update() {

    //update all the processes

}

