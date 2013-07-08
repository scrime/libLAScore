/***************************************************************************
 *            LasInputBuffer.hpp
 *
 *  2012 Florent Berthaut
 *  ANR INEDIT Project
 *
 *  This file is part of libTuiles
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
		LasInputBuffer(LasOutputBuffer*);
		virtual ~LasInputBuffer();
        AudioStreamPtr getStream();
        void prepareStreamChannel(const unsigned int& streamChanID, 
                                            LasInputBuffer* inpBuf, 
                                            bool& triggered);
        
        inline void setChannel(LasChannel* chan){m_channel=chan;}
        uint64_t getAbsPosInFrames();
        inline uint64_t getPositionInFrames(){return m_positionInFrames;}

	protected:
        LasChannel* m_channel;
        LasOutputBuffer* m_connectedBuffer;
        uint64_t m_positionInMs;
        uint64_t m_lengthInMs;
        uint64_t m_positionInFrames;
        uint64_t m_lengthInFrames;
};

}

#endif

