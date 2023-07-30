/*
  ==============================================================================

    Hadamard.cpp
    Created: 29 Jul 2023 2:39:27pm
    Author:  Jacob Zeisel

  ==============================================================================
*/

#include "Hadamard.h"

Hadamard::Hadamard(int size)
{
    hadamard_size = size;
}

void Hadamard::inPlaceTransform(double **current_values)
{
    // input is an array of pointers to each channel's current value
    
    // we want to do a matrix multiplication with our hadamard matrix
    // and then put the result back in the current values matrix
    
    double output_val_one = 0.0;
    double output_val_two = 0.0;
    double output_val_three = 0.0;
    double output_val_four = 0.0;
    
    double* output_vals[4] = {&output_val_one, &output_val_two, &output_val_three, &output_val_four};
    
    // dot products of 1x4 and 4x4 matrices
    for (int i = 0; i < hadamard_size; ++i)
    {
        for (int j = 0; j < hadamard_size; ++j)
        {
            *(output_vals[i]) += matrix[i][j] * (*(current_values[j]));
        }
    }
    
    // put the output vals into the current vals
    for (int i = 0; i < hadamard_size; ++i)
    {
        *(current_values[i]) = *(output_vals[i]);
    }
}
