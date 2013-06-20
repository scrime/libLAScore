/***************************************************************************
 *  LasProcessesManager.hpp
 *  2012- Florent Berthaut
 *  ANR INEDIT Project
 *  This file is part of libLAScore
 ****************************************************************************/

#ifndef LasProcessesManager_h
#define LasProcessesManager_h

#include <vector>
#include <map>

#include <LibAudioStream/LibAudioStream.h>
#include <IScore/Engines.hpp>

class LasProcess;
class LasAudioInputProcess;
class LasAudioOutputProcess;
class LasFaustProcess;
class LasSoundfileProcess;

class LasProcessesManager {
	public:
		static LasProcessesManager* getInstance();
		~LasProcessesManager();

		void update();
        void start();
        void stop();
        void clear();

        LasFaustProcess* createFaustProcess();
        LasSoundfileProcess* createSoundfileProcess();
        inline LasAudioInputProcess* getAudioInputProcess() { 
            return m_audioInputProc;
        }
        inline LasAudioOutputProcess* getAudioOutputProcess() {
            return m_audioOutputProc;
        }

        inline Engines* getIscoreEngines(){return m_engines;}
        inline AudioPlayerPtr getLASPlayer(){return m_player;}

        inline bool isPlaying(){return m_playing;}

	private:
		LasProcessesManager();

    private:
        std::vector<LasProcess*> m_processes;
        std::map<unsigned int, LasProcess*> m_processesMap;

        LasAudioInputProcess* m_audioInputProc;
        LasAudioOutputProcess* m_audioOutputProc;

        Engines* m_engines;
        AudioPlayerPtr m_player;
        unsigned int m_inpChanNb;
        unsigned int m_outChanNb;
        unsigned int m_playChanNb;
        unsigned int m_sampleRate;
        unsigned int m_audioBufSize;
        unsigned int m_rtAudioBufSize;
        unsigned int m_fileBufSize;
        bool m_playing;
};

#endif

