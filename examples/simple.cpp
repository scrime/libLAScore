/***************************************************************************
 *  simple.cpp
 *  2012- Florent Berthaut
 *  ANR INEDIT Project
 *  This file is part of libLASProc
 ****************************************************************************/

#include <iostream>

#include <lascore/LasScoreManager.hpp>
#include <lascore/LasFaustProcess.hpp>
#include <lascore/LasAudioInputProcess.hpp>
#include <lascore/LasAudioOutputProcess.hpp>
#include <lascore/LasSoundfileProcess.hpp>
#include <lascore/LasChannel.hpp>
#include <lascore/LasInputBuffer.hpp>
#include <lascore/LasOutputBuffer.hpp>

using namespace std;
using namespace lascore;

int main(int argc, char* argv) {

    cout<<"Starting the simple example of libLAScore"<<endl;

    //Get the manager
    LasScoreManager* man = LasScoreManager::getInstance();

    //Add an audio input process
    LasAudioInputProcess* audioInput = man->getAudioInputProcess();

    //and an audio output process
    LasAudioOutputProcess* audioOutput = man->getAudioOutputProcess();

    cout<<"Add an echo.dsp faust effect"<<endl;   
    LasFaustProcess* faust1 = man->createFaustProcess();
    faust1->load("examples/echo.dsp");
    faust1->setPositionInMs(2000);
    faust1->setLengthInMs(5000);

    cout<<"Connect it to the main input"<<endl;
    LasOutputBuffer* obuf1 = audioInput->getChannel(0)->addOutputBuffer();
    faust1->getChannel(0)->addInputBuffer(obuf1);

    cout<<"Add drums.wav"<<endl;
    LasSoundfileProcess* sound1 = man->createSoundfileProcess();
    sound1->load("examples/drums.wav");
    sound1->setPositionInMs(1000);
    sound1->setLengthInMs(3000);

    cout<<"Connect the sound file to the faust effect"<<endl;
    LasOutputBuffer* obuf2 = sound1->getChannel(0)->addOutputBuffer();
    faust1->getChannel(0)->addInputBuffer(obuf2);

    cout<<"Connect the effect to the main output"<<endl;
    LasOutputBuffer* obuf3 = faust1->getChannel(0)->addOutputBuffer();
    audioOutput->getChannel(0)->addInputBuffer(obuf3);

    cout<<"Start playing the score"<<endl;
    man->start();

    int time=0;
    int step=100000;
    while(man->isPlaying()) {
        cout<<"time: "<<time/1000<<"ms"<<endl;
        time+=step;
        usleep(step);
    }

    cout<<"Done"<<endl;

    return EXIT_SUCCESS;
}

