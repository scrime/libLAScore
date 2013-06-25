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

int main(int argc, char* argv) {

    cout<<"Starting the simple example of libLAScore"<<endl;

    //Get the manager
    LasScoreManager* man = LasScoreManager::getInstance();

    //Add an audio input process
    LasAudioInputProcess* audioInput = man->getAudioInputProcess();

    //and an audio output process
    LasAudioOutputProcess* audioOutput = man->getAudioOutputProcess();

    //Add a Faust process and set its position
    cout<<"Adding an echo.dsp faust effect"<<endl;   
    LasFaustProcess* faust1 = man->createFaustProcess();
    faust1->load("examples/echo.dsp");
    faust1->setPositionInMs(10);
    faust1->setLengthInMs(5000);

    //Connect it to the audio input and to the audio output 
    cout<<"Connecting it to the main input"<<endl;
    LasOutputBuffer* obuf1 = audioInput->getChannel(0)->addOutputBuffer();
    LasInputBuffer* ibuf1 = faust1->getChannel(0)->addInputBuffer(obuf1);

    //Add a soundfile process  
    cout<<"Adding drums.wav and connecting it to the echo effect"<<endl;
    LasSoundfileProcess* sound1 = man->createSoundfileProcess();
    sound1->load("examples/drums.wav");
    sound1->setPositionInMs(1000);
    sound1->setLengthInMs(3000);

    //Connect it to the faust process
    cout<<"Connecting the sound file to the faust effect"<<endl;
    LasOutputBuffer* obuf2 = sound1->getChannel(0)->addOutputBuffer();
    LasInputBuffer* ibuf2 = faust1->getChannel(0)->addInputBuffer(obuf2);

    //Connect the faust process to the audio output
    cout<<"Connecting the effect to the main output"<<endl;
    LasOutputBuffer* obuf3 = faust1->getChannel(0)->addOutputBuffer();
    LasInputBuffer* ibuf3 = audioOutput->getChannel(0)->addInputBuffer(obuf3);

    //Start the audiograph
    cout<<"Start playing the graph"<<endl;
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

