/***************************************************************************
 *  LasAudioInputProcess.cpp
 *  2012- Florent Berthaut
 *  ANR INEDIT Project
 *  This file is part of libLASProc
 ****************************************************************************/

#include "LasAudioInputProcess.hpp"

using namespace std;

namespace lascore {

LasAudioInputProcess::LasAudioInputProcess(): LasProcess() {
    addChannel();
}

LasAudioInputProcess::~LasAudioInputProcess() {}

AudioStreamPtr LasAudioInputProcess::getStream(LasChannel*) {
    return MakeSharedInputSoundPtr();
}

void LasAudioInputProcess::addChannel() {
    LasProcess::addChannel();
}

void LasAudioInputProcess::load(const std::string& fileStr) {
}

}

