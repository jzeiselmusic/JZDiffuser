/*
  ==============================================================================

    utilities.h
    Created: 29 Jul 2023 3:26:27pm
    Author:  Jacob Zeisel

  ==============================================================================
*/

#pragma once

int incrementModulo(const int current_value, const int max_length)
{
    return current_value + 1 >= max_length ? 0 : current_value + 1;
}
