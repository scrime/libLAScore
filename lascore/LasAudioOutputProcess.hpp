/***************************************************************************
 *            LasSoundfileProcess.hpp
 *
 *  2012 Florent Berthaut
 *  ANR INEDIT Project
 *
 *  This file is part of libTuiles
 ****************************************************************************/


#ifndef LasSoundfileProcess_h
#define LasSoundfileProcess_h

#include "LasProcess.hpp"

class LasSoundfileProcess: public LasProcess {
	public:
		LasSoundfileProcess();
		virtual ~LasSoundfileProcess();

        void addChannel();
        void load(const std::string& fileStr);
	protected:

};

#endif

