/*
  ==============================================================================

    Hadamard.h
    Created: 29 Jul 2023 2:39:32pm
    Author:  Jacob Zeisel

  ==============================================================================
*/

#pragma once

#include <vector>

class Householder {
    
public:
    Householder(int size); // in our case always has to be 4x4
    
    void inPlaceTransform(std::vector<double>* buffer);
    
    std::vector<std::vector<double>> createHouseholder(int size);
    
private:
    int householder_size; // should always equal num channels
    
    std::vector<std::vector<double>> my_matrix;
    
    double matrix_two[2][2] = {{0.0, -1.0}, {-1.0, 0.0}};
    
    double matrix_three[3][3] = {{1.0/3.0, -2.0/3.0 -2.0/3.0},
                                {-2.0/3.0, 1.0/3.0, -2.0/3.0},
                                {-2.0/3.0, -2.0/3.0, 1.0/3.0}};
    double matrix_four[4][4] = { { 1.0/2.0,-1.0/2.0,-1.0/2.0,-1.0/2.0},
                                {-1.0/2.0, 1.0/2.0,-1.0/2.0,-1.0/2.0},
                                {-1.0/2.0,-1.0/2.0, 1.0/2.0,-1.0/2.0},
                                {-1.0/2.0,-1.0/2.0,-1.0/2.0, 1.0/2.0} };
    double matrix_five[5][5] = {{3.0/5.0, -2.0/5.0, -2.0/5.0, -2.0/5.0, -2.0/5.0},
                                {-2.0/5.0, 3.0/5.0, -2.0/5.0, -2.0/5.0, -2.0/5.0},
                                {-2.0/5.0, -2.0/5.0, 3.0/5.0, -2.0/5.0, -2.0/5.0},
                                {-2.0/5.0, -2.0/5.0, -2.0/5.0, 3.0/5.0, -2.0/5.0},
                                {-2.0/5.0, -2.0/5.0, -2.0/5.0, -2.0/5.0, 3.0/5.0}};
};
