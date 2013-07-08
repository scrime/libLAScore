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

namespace lascore {

class LasInputBuffer;
class LasOutputBuffer;
class LasProcess;

class LasChannel {
	public:
		LasChannel();
		virtual ~LasChannel();

        inline void setID(const unsigned int& id) {m_id=id;}
        inline const unsigned int& getID(){return m_id;}

        AudioStreamPtr getInputStream();
        AudioStreamPtr getOutputStream();

        void prepareStreamChannel(const unsigned int& streamChanID, 
                                                LasInputBuffer* inpBuf, 
                                                        bool& triggered);
        inline void setProcess(LasProcess* proc){m_process=proc;}
        inline LasProcess* getProcess(){return m_process;}
        const uint64_t& getLengthInFrames();

        LasOutputBuffer* addOutputBuffer();
        LasInputBuffer* addInputBuffer(LasOutputBuffer*);
        
        inline const std::vector<LasInputBuffer*>& getInputBuffers() {
            return m_inputBuffers;
        }

	protected:
        unsigned int m_id;
        LasProcess* m_process;
        std::vector<LasInputBuffer*> m_inputBuffers;
        std::vector<LasOutputBuffer*> m_outputBuffers;
};

}

#endif

