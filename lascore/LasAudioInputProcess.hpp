/***************************************************************************
 *  LasAudioInputProcess.hpp
 *  2012 Florent Berthaut
 *  ANR INEDIT Project
 *  This file is part of libLAScore
 ****************************************************************************/

#ifndef LasAudioInputProcess_h
#define LasAudioInputProcess_h

#include "LasProcess.hpp"

namespace lascore {

class LasAudioInputProcess: public LasProcess {
	public:
		LasAudioInputProcess();
		virtual ~LasAudioInputProcess();

        void addChannel();
        void load(const std::string& fileStr);

        AudioStreamPtr getStream(LasChannel*);

	protected:

};

}

#endif

