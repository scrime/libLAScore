/***************************************************************************
 *  LasFaustProcess.hpp
 *  2012- Florent Berthaut
 *  ANR INEDIT Project
 *  This file is part of libLAScore
 ****************************************************************************/


#ifndef LasFaustProcess_h
#define LasFaustProcess_h

#include <string>

#include "LasProcess.hpp"

namespace lascore {

class LasFaustProcess: public LasProcess {
	public:
		LasFaustProcess();
		virtual ~LasFaustProcess();

        virtual void addChannel();
        void load(const std::string& effectStr);

        AudioStreamPtr getStream(LasChannel*);

	protected:
        std::string m_effectStr;
        std::vector<AudioEffectListPtr> m_effectLists;
};

}

#endif

