/***************************************************************************
 *  LasProcess.hpp
 *  2012 Florent Berthaut
 *  ANR INEDIT Project
 *  This file is part of libLASProc
 ****************************************************************************/

#ifndef LasProcess_h
#define LasProcess_h

#include <vector>
#include <map>

class LasChannel;
class LasInputBuffer;

class LasProcess {
	public:
		LasProcess();
		virtual ~LasProcess();

        virtual void addChannel()=0;
        LasChannel* getChannel(const unsigned int& c){return m_channels[c];}
        void startChannels();

        inline const unsigned int& getID() {return m_id;}

        void setPositionMs(const unsigned long& pos);
        void setLengthMs(const unsigned long& length);

    protected:
        void updateBox();

	protected:
        unsigned int m_id;
        unsigned long m_positionMs;
        unsigned long m_lengthMs;

        std::vector<LasChannel*> m_channels;
        std::map<unsigned int, LasInputBuffer*> m_streamChannelMap;
};

#endif

