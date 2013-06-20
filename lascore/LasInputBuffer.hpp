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

class LasChannel;
class LasOutputBuffer;

class LasInputBuffer {
	public:
		LasInputBuffer(LasOutputBuffer*);
		virtual ~LasInputBuffer();
        AudioStreamPtr getStream();

	protected:
        LasChannel* m_channel;
        LasOutputBuffer* m_connectedBuffer;
};

#endif

