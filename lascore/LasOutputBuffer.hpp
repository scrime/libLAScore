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

	protected:
        LasChannel* m_channel;
        std::vector<LasInputBuffer*> m_connectedBuffers;
};

#endif

