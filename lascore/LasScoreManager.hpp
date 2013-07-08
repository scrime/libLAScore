/***************************************************************************
 *  LasScoreManager.hpp
 *  2012- Florent Berthaut
 *  ANR INEDIT Project
 *  This file is part of libLAScore
 ****************************************************************************/

#ifndef LasScoreManager_h
#define LasScoreManager_h

#include <vector>
#include <map>

#include <LibAudioStream/LibAudioStream.h>
#include <IScore/Engines.hpp>

namespace lascore {

class LasProcess;
class LasAudioInputProcess;
class LasAudioOutputProcess;
class LasFaustProcess;
class LasSoundfileProcess;

class LasScoreManager {
	public:
		static LasScoreManager* getInstance();
		~LasScoreManager();

		void update();
        void start();
        void stop();
        void clear();

        LasFaustProcess* createFaustProcess();
        LasSoundfileProcess* createSoundfileProcess();
        LasAudioInputProcess* getAudioInputProcess();
        LasAudioOutputProcess* getAudioOutputProcess();

        inline Engines* getIscoreEngines(){return m_engines;}
        inline AudioPlayerPtr getLASPlayer(){return m_player;}

        inline bool isPlaying(){return m_playing;}

        uint64_t msToFrames(const uint64_t&);

    protected:
        friend void isExecutionFinishedCallBack();
        friend void waitedTriggerPointCallBack(bool isWaited, 
                                                unsigned int triggerId, 
                                                unsigned int boxId, 
                                                unsigned int controlPointIndex, 
                                                std::string triggerMessage);
        friend void controlPointCallBack(  
                                    unsigned int boxId, 
                                    unsigned int controlPointIndex, 
                                    std::vector<unsigned int> processToStop);

	private:
		LasScoreManager();

    private:
        std::vector<LasProcess*> m_processes;
        std::map<int, LasProcess*> m_processesMap;

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

}

#endif

