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
    Diffuser(double length, int size, double sampleRate, int rd_seed); // length of diffusion in seconds
    
    double processAndReturnSample(double sample);
    
private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Diffuser);
    
    void invertSamples(std::vector<double>*); // second part is a multichannel inverter and/or swapper
    void hadamardTransform(std::vector<double>*); // third part is pass multiple channels through a hadamard matrix
    
    int random_seed;
    
    int size;
    
    // declare a delay module
    // but dont initialize until we have been given a random seed
    Delayer* delay_module;
    
    std::vector<double> audio_buffer;
    
    // declare the hadamard object we will use
    Householder* householder_matrix;
    
    // this is the 4-channel inverter made randomly
    // start it with all non-inversions
    std::vector<int> inverter;
};
