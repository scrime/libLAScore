/***************************************************************************
 *  LasInputBuffer.hpp
 *  2012- Florent Berthaut
 *  ANR INEDIT Project
 *  This file is part of libLAScore
 ****************************************************************************/


#ifndef LasInputBuffer_h
#define LasInputBuffer_h

#include <stdint.h>
#include <LibAudioStream/LibAudioStream.h>

namespace lascore {

class LasChannel;
class LasOutputBuffer;

class LasInputBuffer {
	public:
		LasInputBuffer(LasChannel*, LasOutputBuffer*);
		virtual ~LasInputBuffer();
        AudioStreamPtr getStream();
        void prepareStreamChannel(const unsigned int& streamChanID, 
                                            LasInputBuffer* inpBuf, 
                                            bool& triggered);
        void setPositionInMs(const uint64_t&);
        uint64_t getAbsPosInFrames();
        uint64_t getPositionInFrames();
        inline const int& getID(){return m_id;}
        void updateBox();

    protected:
        void editBox();

	protected:
        int m_id;
        LasChannel* m_channel;
        LasOutputBuffer* m_connectedBuffer;
        uint64_t m_positionInMs;
        uint64_t m_lengthInMs;
        uint64_t m_positionInFrames;
        uint64_t m_lengthInFrames;
};

}

#endif

