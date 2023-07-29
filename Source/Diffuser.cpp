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

using namespace juce;

Diffuser::Diffuser(double length, double sampleRate)
{
    buffer_length = (int)(length*sampleRate + 1.0);
    // we have 4 channels to work with
    // each channel and delay line needs to be length*sampleRate num samples
    audio_channels = AudioBuffer<double>(4, buffer_length);
    delay_channels = AudioBuffer<double>(4, buffer_length);
    
    // clear to set to all zeroes initiallly
    audio_channels.clear();
    delay_channels.clear();
    
    // decide how much delay each of the channels should have
    int increment = buffer_length / 4;
    delay_one = increment*1;
    delay_two = increment*2;
    delay_three = increment*3;
    delay_four = increment*4;
    
    // start all indexes at 0
    delay_index_one = 0;
    delay_index_two = 0;
    delay_index_three = 0;
    delay_index_four = 0;
    read_index = 0;
    write_index = 0;
}

void Diffuser::addSample(double sample)
{
    /* add sample to current write pointer */
    
    /* go through each channel and add the same input value to all of them */
    for (int i = 0; i < audio_channels.getNumChannels(); i++)
    {
        auto* write_pointer = audio_channels.getWritePointer(i, write_index);
        *write_pointer = sample;
    }
}

void Diffuser::delaySamples(void)
{
    // first we read the latest sample that was just added from the channel buffer
    
    // then we read the value from the current delay buffer
    // and put that value in the corresponding channel
    
    // then we put the latest channel sample into the delay buffer
    
    // increment the delay buffer pointer
    
    for (int i = 0; i < audio_channels.getNumChannels(); i++)
    {
        auto* read_pointer = audio_channels.getReadPointer(i, read_index);
        double latest_value = *read_pointer;
        
        auto* delay_read_pointer = delay_channels.getReadPointer(i, *(delay_indexes[i]));
        double current_delay_buffer_value = *delay_read_pointer;
        
        auto* write_pointer = audio_channels.getWritePointer(i, write_index);
        *write_pointer = current_delay_buffer_value;
        
        auto* delay_write_pointer = delay_channels.getWritePointer(i, *(delay_indexes[i]));
        *delay_write_pointer = latest_value;
        
        *(delay_indexes[i]) = incrementModulo(*(delay_indexes[i]), *(delay_values[i]));
    }
}

void Diffuser::invertSamples(void)
{
    // go through each channels current value and invert them randomly
    // by randomly, I mean just pick
    
    auto* read_pointer_one = audio_channels.getReadPointer(0, read_index);
    auto* write_pointer_one = audio_channels.getWritePointer(0, write_index);
    
    //auto* read_pointer_two = audio_channels.getReadPointer(1, read_index);
    auto* write_pointer_two = audio_channels.getWritePointer(1, write_index);
    
    auto* read_pointer_three = audio_channels.getReadPointer(2, read_index);
    auto* write_pointer_three = audio_channels.getWritePointer(2, write_index);
    
    auto* read_pointer_four = audio_channels.getReadPointer(3, read_index);
    auto* write_pointer_four = audio_channels.getWritePointer(3, write_index);
    
    double temp = *read_pointer_four;
    double temp_two = *read_pointer_one;
    
    *write_pointer_four = *read_pointer_one;
    
    *write_pointer_one = -(*read_pointer_three);
    
    *write_pointer_two = temp;
    
    *write_pointer_three = -temp_two;
}

void Diffuser::hadamardMatrix(void)
{
    // make an array of pointers to the current channel values
    double channels[4] = {  *(audio_channels.getReadPointer(0, read_index)),
                            *(audio_channels.getReadPointer(1, read_index)),
                            *(audio_channels.getReadPointer(2, read_index)),
                            *(audio_channels.getReadPointer(3, read_index)) };
    
    Hadamard<double, 4>::inPlace(channels);
    
    for (int i = 0; i < audio_channels.getNumChannels(); i++)
    {
        auto* write_pointer = audio_channels.getWritePointer(i, write_index);
        *write_pointer = channels[i];
    }
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
    
    invertSamples();
    
    hadamardMatrix();
    
    auto* channel_one_output_pointer = audio_channels.getReadPointer(0, read_index);
    auto* channel_two_output_pointer = audio_channels.getReadPointer(1, read_index);
    auto* channel_three_output_pointer = audio_channels.getReadPointer(2, read_index);
    auto* channel_four_output_pointer = audio_channels.getReadPointer(3, read_index);
    
    double channel_one_output_value = *channel_one_output_pointer;
    double channel_two_output_value = *channel_two_output_pointer;
    double channel_three_output_value = *channel_three_output_pointer;
    double channel_four_output_value = *channel_four_output_pointer;
    
    /* output is the sum of the multichannel matrix */
    double output_value =   (channel_one_output_value + channel_two_output_value + channel_three_output_value + channel_four_output_value) / 4.0;
    
    /* make sure to increment the read pointer now, modulo the length of the buffer */
    read_index = incrementModulo(read_index, buffer_length);
    
    /* make sure to increment the write index */
    write_index = incrementModulo(write_index, buffer_length);
    
    return output_value;
}
