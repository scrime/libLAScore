/***************************************************************************
 *  LasFaustProcess.hpp
 *  2012- Florent Berthaut
 *  ANR INEDIT Project
 *  This file is part of libTuiles
 ****************************************************************************/


#ifndef LasFaustProcess_h
#define LasFaustProcess_h

#include <string>

#include "LasProcess.hpp"

class LasFaustProcess: public LasProcess {
	public:
		LasFaustProcess();
		virtual ~LasFaustProcess();

        void addChannel();
        void load(const std::string& effectStr);

	protected:
        std::string m_effectStr;

};

#endif

