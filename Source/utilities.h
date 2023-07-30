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

int getRandomInRange(int maxValue, std::mt19937 gen)
{
    // return a random number between -(maxValue/2) to (maxValue/2)

    // Define the distribution for the random numbers (1 or -1)
    std::uniform_int_distribution<> mult_distrib(0, 1);

    // Generate a random number (0 or 1)
    int randomMult = mult_distrib(gen);

    // Convert 0 to -1 and 1 to 1 and return the result
    int multiplier = (randomMult == 0) ? -1 : 1;
    
    // Define new distribution between 0 and maxValue/2
    std::uniform_int_distribution<> total_distrib(0, maxValue/2);
    
    // random int between 0 and maxValue/2
    int randomValue = total_distrib(gen);
    
    // return + / - the random value
    return randomValue * multiplier;
}
