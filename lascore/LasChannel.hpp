/***************************************************************************
 *  LasChannel.hpp
 *  2012 Florent Berthaut
 *  ANR INEDIT Project
 *  This file is part of libLAScore
 ****************************************************************************/

#ifndef LasChannel_h
#define LasChannel_h

#include <stdint.h>
#include <vector>
#include <LibAudioStream/LibAudioStream.h>

class LasInputBuffer;
class LasOutputBuffer;

class LasChannel {
	public:
		LasChannel(const unsigned int& id);
		virtual ~LasChannel();

        AudioStreamPtr getStream();

        inline void getID(const unsigned int& id){m_id=id;}
        inline const unsigned int& getID(){return m_id;}

        LasOutputBuffer* addOutputBuffer();
        LasInputBuffer* addInputBuffer(LasOutputBuffer*);

	protected:
        unsigned int m_id;
        std::vector<LasInputBuffer*> m_inputBuffers;
        std::vector<LasOutputBuffer*> m_outputBuffers;
};

#endif

