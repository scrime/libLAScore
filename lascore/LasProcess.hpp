/***************************************************************************
 *  LasProcess.hpp
 *  2012 Florent Berthaut
 *  ANR INEDIT Project
 *  This file is part of libLAScore
 ****************************************************************************/

#ifndef LasProcess_h
#define LasProcess_h

#include <vector>
#include <map>
#include <LibAudioStream/LibAudioStream.h>

class LasChannel;
class LasInputBuffer;

class LasProcess {
	public:
		LasProcess();
		virtual ~LasProcess()=0;

        virtual void addChannel();
        LasChannel* getChannel(const unsigned int& c){return m_channels[c];}
        void start();
        void stop();

        inline const unsigned int& getID() {return m_id;}

        void setPositionInMs(const uint64_t& pos);
        void setLengthInMs(const uint64_t& length);

        inline const uint64_t& getPositionInMs(){return m_positionInMs;}
        inline const uint64_t& getLengthInMs(){return m_lengthInMs;}
        inline const uint64_t& getPositionInFrames(){return m_positionInFrames;}
        inline const uint64_t& getLengthInFrames(){return m_lengthInFrames;}

        virtual AudioStreamPtr getStream(LasChannel*);
        void prepareStreamChannel(const unsigned int& streamChanID, 
                                                LasInputBuffer* inpBuf, 
                                                        bool& triggered);

        inline void enableInteractionPoint(){m_triggered=true;}
        inline void disableInteractionPoint(){m_triggered=false;}

    protected:
        void updateBox();

	protected:
        unsigned int m_id;
        uint64_t m_positionInMs;
        uint64_t m_lengthInMs;
        uint64_t m_positionInFrames;
        uint64_t m_lengthInFrames;
        bool m_triggered;

        std::vector<LasChannel*> m_channels;
        std::map<unsigned int, 
                std::vector<LasInputBuffer*> > m_streamChannelMap;
};

#endif

