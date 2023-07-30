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

Diffuser::Diffuser(double length, double sampleRate, int rd)
{
    printf("length = %f, sR = %f\n", length, sampleRate);
    buffer_length = length*sampleRate + 1;
    printf("buffer length = %d\n", buffer_length);
    // we have 4 channels to work with
    // each delay line needs to be length*sampleRate num samples
    delay_channel_one = (double*)calloc(buffer_length, sizeof(double));
    delay_channel_two = (double*)calloc(buffer_length, sizeof(double));
    delay_channel_three = (double*)calloc(buffer_length, sizeof(double));
    delay_channel_four = (double*)calloc(buffer_length, sizeof(double));
    
    delay_channels[0] = delay_channel_one;
    delay_channels[1] = delay_channel_two;
    delay_channels[2] = delay_channel_three;
    delay_channels[3] = delay_channel_four;
    
    // random number generation. we need 3 seeds from a single random device
    std::mt19937 gen1(rd);
    std::mt19937 gen2(rd + 10);
    std::mt19937 gen3(rd + 20);
        
    // decide how much delay each of the channels should have
    int increment = buffer_length / 4;
    delay_one = increment + getRandomInRange(increment, gen1);
    printf("delay_one length = %d\n", delay_one);
    delay_two = increment*2 + getRandomInRange(increment, gen2);
    printf("delay_two length = %d\n", delay_two);
    delay_three = increment*3 + getRandomInRange(increment, gen3);
    printf("delay_three length = %d\n", delay_three);
    delay_four = increment*4;
    printf("delay_four length = %d\n", delay_four);
    
    // start all indexes at 0
    delay_index_one = 0;
    delay_index_two = 0;
    delay_index_three = 0;
    delay_index_four = 0;
}

void Diffuser::addSample(double sample)
{
    /* add sample to current write pointer */
    
    /* go through each channel and add the same input value to all of them */
    for (int i = 0; i < 4; ++i)
    {
        audio_buffer[i] = sample;
    }
}

void Diffuser::delaySamples(void)
{
    // first we read the latest sample that was just added from the channel buffer
    
    // then we read the value from the current delay buffer
    // and put that value in the corresponding channel
    
    // then we put the latest channel sample into the delay buffer
    
    // increment the delay buffer pointer
    
    for (int i = 0; i < 4; ++i)
    {
        double latest_value = audio_buffer[i]; // should be the same every pass through
        
        double current_delay_buffer_value = delay_channels[i][*(delay_indexes[i])];
        
        audio_buffer[i] = current_delay_buffer_value;
        
        delay_channels[i][*(delay_indexes[i])] = latest_value;
        
        *(delay_indexes[i]) = incrementModulo(*(delay_indexes[i]), *(delay_values[i]));
    }
}

void Diffuser::invertSamples(void)
{
    // go through each channels current value and invert them randomly
    // by randomly, I mean just pick
}

void Diffuser::hadamardMatrix(void)
{
    // make an array of pointers to the current channel values
    double* channels[4] = { &audio_buffer[0],
                            &audio_buffer[1],
                            &audio_buffer[2],
                            &audio_buffer[3] };
    
    hadamard_matrix.inPlaceTransform(channels);
}

/*
    this method should be called by user,
    should take in a sample and return an output, all while
    updating the current state of the buffers in the diffuser system.
*/
double Diffuser::processAndReturnSample(double sample)
{
    addSample(sample);
    
    //
    // do processing here
    //
    
    delaySamples();
    
    //invertSamples();
    
    //hadamardMatrix();
    
    /* output is the sum of the multichannel matrix */
    double output_value =   audio_buffer[0] + audio_buffer[1] + audio_buffer[2] + audio_buffer[3];
    
    return output_value;
}
