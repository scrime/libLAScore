/***************************************************************************
 *            LasAudioInputProcess.hpp
 *
 *  2012 Florent Berthaut
 *  ANR INEDIT Project
 *
 *  This file is part of libTuiles
 ****************************************************************************/


#ifndef LasAudioInputProcess_h
#define LasAudioInputProcess_h

#include "LasProcess.hpp"

class LasAudioInputProcess: public LasProcess {
	public:
		LasAudioInputProcess();
		virtual ~LasAudioInputProcess();

        inline void addChannel(){}

	protected:

};

#endif

