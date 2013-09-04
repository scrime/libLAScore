/***************************************************************************
 *  LasOutputBuffer.hpp
 *  2012- Florent Berthaut
 *  ANR INEDIT Project
 *  This file is part of libLASProc
 ****************************************************************************/

#ifndef LasOutputBuffer_h
#define LasOutputBuffer_h

#include <stdint.h>
#include <LibAudioStream/LibAudioStream.h>
#include <vector>

namespace lascore {

class LasChannel;
class LasInputBuffer;

class LasOutputBuffer {
	public:
		LasOutputBuffer(LasChannel*);
		virtual ~LasOutputBuffer();
        void connectBuffer(LasInputBuffer*);

        AudioStreamPtr getStream();
        
        void setPositionInMs(const uint64_t&);
        void setLengthInMs(const uint64_t&);
        const uint64_t& getPositionInMs();
        const uint64_t& getAbsolutePositionInMs();
        const uint64_t& getLengthInMs();
        const uint64_t& getPositionInFrames();
        const uint64_t& getLengthInFrames();

        void prepareStreamChannel(const unsigned int& streamChanID, 
                                            LasInputBuffer* inpBuf, 
                                            bool& triggered);
        inline const int& getID(){return m_id;}
        void updateBox();
        
    protected:
        void testEditBox(const uint64_t& pos, const uint64_t& length);

	protected:
        int m_id;
        uint64_t m_positionInMs;
        uint64_t m_absolutePositionInMs;
        uint64_t m_lengthInMs;
        uint64_t m_positionInFrames;
        uint64_t m_lengthInFrames;
        LasChannel* m_channel;
        std::vector<LasInputBuffer*> m_connectedBuffers;
};

}

#endif

