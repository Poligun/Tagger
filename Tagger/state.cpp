//
//  state.cpp
//  Tagger
//
//  Created by ZhaoYuhan on 3/6/16.
//  Copyright © 2016 ZhaoYuhan. All rights reserved.
//

#include "state.hpp"

void State::addEmission(const std::string& word)
{
    auto iterator = emissionFrequencies.find(word);

    if (iterator == emissionFrequencies.end())
        emissionFrequencies[word] = 1;
    else
        iterator->second++;

    sumOfFrequencies++;
}
