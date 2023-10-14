/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "Diffuser.h"
#include <random>
//==============================================================================
/**
*/
class DiffuserAudioProcessor  : public juce::AudioProcessor
{
public:
    //==============================================================================
    DiffuserAudioProcessor();
    ~DiffuserAudioProcessor() override;

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    //==============================================================================
    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const juce::String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const juce::String getProgramName (int index) override;
    void changeProgramName (int index, const juce::String& newName) override;

    //==============================================================================
    void getStateInformation (juce::MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;

private:
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DiffuserAudioProcessor)
    
    // random seed
    int seed = rand()%100;
    
    // give them the same random generator so each side will sound the same
    Diffuser diffuser_left = Diffuser(.01, 4, 44100.0, seed);
    Diffuser diffuser_right = Diffuser(.01, 4, 44100.0, seed);
    
    Diffuser diffuser_left_one = Diffuser(.09, 4, 44100.0, seed+1);
    Diffuser diffuser_right_one = Diffuser(.09, 4, 44100.0, seed+1);
    
    Diffuser diffuser_left_two = Diffuser(.11, 4, 44100.0, seed+2);
    Diffuser diffuser_right_two = Diffuser(.11, 4, 44100.0, seed+2);
    
    Diffuser diffuser_left_three = Diffuser(.15, 4, 44100.0, seed+3);
    Diffuser diffuser_right_three = Diffuser(.15, 4, 44100.0, seed+3);
    
    Diffuser diffuser_left_four = Diffuser(.2, 4, 44100.0, seed+4);
    Diffuser diffuser_right_four = Diffuser(.2, 4, 44100.0, seed+4);
};
