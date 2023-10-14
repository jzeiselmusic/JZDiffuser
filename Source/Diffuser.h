/*
  ==============================================================================

    Diffuser.h
    Created: 29 Jul 2023 2:38:45pm
    Author:  Jacob Zeisel

  ==============================================================================
*/
#pragma once

#include "JuceHeader.h"
#include "Hadamard.h"
#include "Delayer.h"
#include <random>

using namespace juce;

class Diffuser {
    
public:
    Diffuser(double length, double sampleRate, int rd_seed); // length of diffusion in seconds
    
    double processAndReturnSample(double sample);
    
private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Diffuser);
    
    void invertSamples(void); // second part is a multichannel inverter and/or swapper
    void hadamardMatrix(void); // third part is pass multiple channels through a hadamard matrix
    
    int random_seed;
    
    // declare a delay module
    // but dont initialize until we have been given a random seed
    Delayer* delay_module;
    
    double audio_buffer[4] = {0.0,0.0,0.0,0.0};
    
    // declare the hadamard object we will use
    Householder householder_matrix = Householder(4);
    
    // this is the 4-channel inverter made randomly
    // start it with all non-inversions
    int inverter[4] = {1, 1, 1, 1};
};
