/*
  ==============================================================================

    Hadamard.h
    Created: 29 Jul 2023 2:39:32pm
    Author:  Jacob Zeisel

  ==============================================================================
*/

#pragma once

class Householder {
    
public:
    Householder(int size); // in our case always has to be 4x4
    
    void inPlaceTransform(double* current_values);
    
private:
    int householder_size; // should always equal num channels
    double matrix[4][4] = { { 1.0/2.0,-1.0/2.0,-1.0/2.0,-1.0/2.0},
                            {-1.0/2.0, 1.0/2.0,-1.0/2.0,-1.0/2.0},
                            {-1.0/2.0,-1.0/2.0, 1.0/2.0,-1.0/2.0},
                            {-1.0/2.0,-1.0/2.0,-1.0/2.0, 1.0/2.0} };
};
