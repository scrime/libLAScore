/***************************************************************************
 *            LasAudioOutputProcess.hpp
 *
 *  2012 Florent Berthaut
 *  ANR INEDIT Project
 *
 *  This file is part of libTuiles
 ****************************************************************************/


#ifndef LasAudioOutputProcess_h
#define LasAudioOutputProcess_h

#include "LasProcess.hpp"

class LasAudioOutputProcess: public LasProcess {
	public:
		LasAudioOutputProcess();
		virtual ~LasAudioOutputProcess();

        inline void addChannel(){}

	protected:

};

#endif

