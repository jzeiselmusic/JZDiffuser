/*
  ==============================================================================

    Hadamard.h
    Created: 29 Jul 2023 2:39:32pm
    Author:  Jacob Zeisel

  ==============================================================================
*/

#pragma once

#include <cmath>

// Use like `Hadamard<double, 8>::inPlace(data)` - size must be a power of 2
template<typename Sample, int size>
class Hadamard {
public:
    static inline void recursiveUnscaled(Sample * data) {
        if (size <= 1) return;
        constexpr int hSize = size/2;

        // Two (unscaled) Hadamards of half the size
        Hadamard<Sample, hSize>::recursiveUnscaled(data);
        Hadamard<Sample, hSize>::recursiveUnscaled(data + hSize);

        // Combine the two halves using sum/difference
        for (int i = 0; i < hSize; ++i) {
            double a = data[i];
            double b = data[i + hSize];
            data[i] = (a + b);
            data[i + hSize] = (a - b);
        }
    }

    static inline void inPlace(Sample * data) {
        recursiveUnscaled(data);
        
        Sample scalingFactor = std::sqrt(1.0/size);
        for (int c = 0; c < size; ++c) {
            data[c] *= scalingFactor;
        }
    }
};
