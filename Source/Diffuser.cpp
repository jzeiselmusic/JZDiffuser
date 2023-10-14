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

Diffuser::Diffuser(double length, double sampleRate, int rd_seed)
{
    
    this->delay_module = new Delayer(length, 4, sampleRate, rd_seed);
    
    for (int i = 0; i < 4; ++i)
    {
        std::mt19937 temp(rd_seed);
        inverter[i] = getRandomMult(temp);
    }
}

void Diffuser::invertSamples(void)
{
    // go through each channels current value and invert them randomly
    for (int i = 0; i < 4; ++i)
    {
        audio_buffer[i] *= inverter[i];
    }
}

void Diffuser::hadamardMatrix(void)
{
    householder_matrix.inPlaceTransform(audio_buffer);
}

/*
    this method should be called by user,
    should take in a sample and return an output, all while
    updating the current state of the buffers in the diffuser system.
*/
double Diffuser::processAndReturnSample(double sample)
{
    delay_module->process(sample);
    
    std::vector<double> output = delay_module->getSamples();
    
    for (int i = 0; i < 4; ++i)
    {
        audio_buffer[i] = output[i];
    }
    
    invertSamples();
    
    hadamardMatrix();
    
    /* output is the sum of the multichannel matrix */
    double output_value =   audio_buffer[0] + audio_buffer[1] + audio_buffer[2] + audio_buffer[3];
    
    return output_value;
}
