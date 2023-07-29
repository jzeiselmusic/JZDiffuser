/*
  ==============================================================================

    Diffuser.h
    Created: 29 Jul 2023 2:38:45pm
    Author:  Jacob Zeisel

  ==============================================================================
*/
#pragma once

#include "JuceHeader.h"

using namespace juce;

class Diffuser {
    
public:
    Diffuser(double length, double sampleRate); // length of diffusion in seconds
    
    double processAndReturnSample(double sample);
    
private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Diffuser);
    
    void addSample(double sample); // take in a single channel and add to all channels (4)
    void delaySamples(void); // first part of the diffuser is a multichannel static delay
    void invertSamples(void); // second part is a multichannel inverter and/or swapper
    void hadamardMatrix(void); // third part is pass multiple channels through a hadamard matrix
    
    AudioBuffer<double> audio_channels;
    
    AudioBuffer<double> delay_channels;
    
    // amount of delay for each channel
    // should be random
    int delay_one;
    int delay_two;
    int delay_three;
    int delay_four;
    int* delay_values[4] = {&delay_one, &delay_two, &delay_three, &delay_four};
    
    // current location of the read and write pointer for each delay buffer
    int delay_index_one;
    int delay_index_two;
    int delay_index_three;
    int delay_index_four;
    int* delay_indexes[4] = {&delay_index_one, &delay_index_two, &delay_index_three, &delay_index_four};
    
    // the current location of the input(write) pointer index and output(read) pointer index
    int read_index;
    int write_index;
    
    // the number of samples in the buffer, based on length
    int buffer_length;
};
