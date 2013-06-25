/***************************************************************************
 *  LasSoundfileProcess.hpp
 *  2012 Florent Berthaut
 *  ANR INEDIT Project
 *  This file is part of libLAScore
 ****************************************************************************/


#ifndef LasSoundfileProcess_h
#define LasSoundfileProcess_h

#include "LasProcess.hpp"

#include <string>

class LasSoundfileProcess: public LasProcess {
	public:
		LasSoundfileProcess();
		virtual ~LasSoundfileProcess();

        void addChannel();
        void load(const std::string& fileStr);

        AudioStreamPtr getStream(LasChannel*);

	protected:
        std::string m_fileName;
        std::vector<char> m_fileNameChars;
};

#endif

