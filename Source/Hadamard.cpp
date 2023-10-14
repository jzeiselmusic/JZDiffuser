/*
  ==============================================================================

    Hadamard.cpp
    Created: 29 Jul 2023 2:39:27pm
    Author:  Jacob Zeisel

  ==============================================================================
*/

#include "Hadamard.h"

Householder::Householder(int size)
{
    householder_size = size;
}

void Householder::inPlaceTransform(double* current_values)
{
    // input is an array of pointers to each channel's current value
    
    // we want to do a matrix multiplication with our hadamard matrix
    // and then put the result back in the current values matrix
    
    double output_vals[4] = {0, 0, 0, 0};
    
    // dot products of 1x4 and 4x4 matrices
    for (int i = 0; i < householder_size; ++i)
    {
        for (int j = 0; j < householder_size; ++j)
        {
            output_vals[i] += matrix_four[i][j] * current_values[j];
        }
        // now scale by 1/4
        output_vals[i] *= 0.5;
    }
    
    // put the output vals into the current vals
    for (int i = 0; i < householder_size; ++i)
    {
        current_values[i] = output_vals[i];
    }
}

std::vector<std::vector<double>> Householder::createHouseholder(<#int size#>)
{
    /* create and return a dynamic vector that is a square householder matrix */
    
    return (std::vector<std::vector<double>>)NULL;
}
