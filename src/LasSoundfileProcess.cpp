/***************************************************************************
 *  LasSoundfileProcess.cpp
 *  2012- Florent Berthaut
 *  ANR INEDIT Project
 *  This file is part of libLAScore
 ****************************************************************************/

#include "LasSoundfileProcess.hpp"

using namespace std;

namespace lascore {

LasSoundfileProcess::LasSoundfileProcess(): LasProcess() {
    addChannel();
}

LasSoundfileProcess::~LasSoundfileProcess() {}

AudioStreamPtr LasSoundfileProcess::getStream(LasChannel*) {
    return MakeReadSoundPtr(&m_fileNameChars[0]);
}

void LasSoundfileProcess::addChannel() {
    LasProcess::addChannel();
}

void LasSoundfileProcess::load(const std::string& fileStr) {
    m_fileName=fileStr;
    m_fileNameChars.resize(m_fileName.size() + 1);
    copy(m_fileName.begin(), m_fileName.end(), m_fileNameChars.begin());
}

}

