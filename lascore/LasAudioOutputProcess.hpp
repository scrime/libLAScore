/***************************************************************************
 *  LasAudioOutputProcess.hpp
 *  2012 Florent Berthaut
 *  ANR INEDIT Project
 *  This file is part of libLAScore
 ****************************************************************************/

#ifndef LasAudioOutputProcess_h
#define LasAudioOutputProcess_h

#include "LasProcess.hpp"

class LasAudioOutputProcess: public LasProcess {
	public:
		LasAudioOutputProcess();
		virtual ~LasAudioOutputProcess();

        void addChannel();
        void load(const std::string& fileStr);

        void prepareStreamChannels();
	protected:

};

#endif

