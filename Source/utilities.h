/*
  ==============================================================================

    utilities.h
    Created: 29 Jul 2023 3:26:27pm
    Author:  Jacob Zeisel

  ==============================================================================
*/

#pragma once
#include <random>

int incrementModulo(const int current_value, const int max_length)
{
    return current_value + 1 >= max_length ? 0 : current_value + 1;
}

int getRandomMult(std::mt19937 gen)
{
    // return either 1 or -1
    
    std::uniform_int_distribution<> mult_distrib(0,1);
    
    int randomMult = mult_distrib(gen);
    
    return (randomMult == 0) ? -1 : 1;
}

int getRandomInRange(int maxValue, std::mt19937 gen)
{
    // return a random number between -(maxValue/2) to (maxValue/2)

    int multiplier = getRandomMult(gen);
    
    // Define new distribution between 0 and maxValue/2
    std::uniform_int_distribution<> total_distrib(0, maxValue/2);
    
    // random int between 0 and maxValue/2
    int randomValue = total_distrib(gen);
    
    // return + / - the random value
    return randomValue * multiplier;
}
