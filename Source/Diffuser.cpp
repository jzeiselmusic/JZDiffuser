/*
  ==============================================================================

    Diffuser.cpp
    Created: 29 Jul 2023 2:38:40pm
    Author:  Jacob Zeisel

  ==============================================================================
*/

#include "Diffuser.h"
#include "utilities.h"
#include "Hadamard.h"
#include <random>

using namespace juce;

Diffuser::Diffuser(double length, int size, double sampleRate, int rd_seed)
{
    
    this->delay_module = new Delayer(length, size, sampleRate, rd_seed);
    
    this->size = size;
    
    for (int i = 0; i < size; ++i)
    {
        std::mt19937 temp(rd_seed);
        inverter.push_back(getRandomMult(temp));
    }
    
    /* set the audio buffer to all zeros */
    audio_buffer.resize(size);
    std::fill(audio_buffer.begin(), audio_buffer.end(), 0.0);
    
    this->householder_matrix = new Householder(size);
}

void Diffuser::invertSamples(std::vector<double>* buffer)
{
    // go through each channels current value and invert them randomly
    for (int i = 0; i < this->size; ++i)
    {
        buffer->at(i) *= inverter[i];
    }
}

void Diffuser::hadamardTransform(std::vector<double>* buffer)
{
    householder_matrix->inPlaceTransform(buffer);
}

/*
    this method should be called by user,
    should take in a sample and return an output, all while
    updating the current state of the buffers in the diffuser system.
*/
double Diffuser::processAndReturnSample(double sample)
{
    delay_module->process(sample);
    
    std::vector<double>* output = delay_module->getSamples();
    
    invertSamples(output);
    
    hadamardTransform(output);
    
    /* output is the sum of the multichannel matrix */
    double output_sample = 0.0;
    for (int i = 0; i < this->size; ++i)
    {
        output_sample += output->at(i);
    }
    
    return output_sample;
}
