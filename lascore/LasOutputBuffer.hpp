/***************************************************************************
 *            LasOutputBuffer.hpp
 *
 *  2012 Florent Berthaut
 *  ANR INEDIT Project
 *
 *  This file is part of libTuiles
 ****************************************************************************/


#ifndef LasOutputBuffer_h
#define LasOutputBuffer_h

#include <stdint.h>
#include <LibAudioStream/LibAudioStream.h>
#include <vector>

class LasChannel;
class LasInputBuffer;

class LasOutputBuffer {
	public:
		LasOutputBuffer();
		virtual ~LasOutputBuffer();
        void connectBuffer(LasInputBuffer*);

        AudioStreamPtr getStream();
        
        void prepareStreamChannel(const unsigned int& streamChanID, 
                                            LasInputBuffer* inpBuf, 
                                            bool& triggered);
        void setChannel(LasChannel* chan);

	protected:
        uint64_t m_positionInFrames;
        uint64_t m_lengthInFrames;
        LasChannel* m_channel;
        std::vector<LasInputBuffer*> m_connectedBuffers;
};

#endif

