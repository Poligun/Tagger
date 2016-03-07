//
//  transition.cpp
//  Tagger
//
//  Created by ZhaoYuhan on 3/6/16.
//  Copyright © 2016 ZhaoYuhan. All rights reserved.
//

#include "transition.hpp"

Transition& Transition::getTransition(const std::string* stateNames[], int size)
{
    auto transition = this;

    for (int i = 0; i < size; i++)
        transition = transition->transitionMap[*stateNames[i]];
    return *transition;
}

const Transition& Transition::getTransition(const std::string* stateNames[], int size) const
{
    return getTransition(stateNames, size);
}

void Transition::addTransition(const std::string* stateNames[], int size, const std::string& targetStateName)
{
    auto& stateFrequencies = getTransition(stateNames, size).stateFrequencies;
    auto iterator = stateFrequencies.find(targetStateName);

    if (iterator == stateFrequencies.end())
        stateFrequencies[targetStateName] = 1;
    else
        iterator->second++;

    sumOfFrequencies++;
}

Transition::~Transition()
{
    for (auto iterator = transitionMap.begin(); iterator != transitionMap.end(); iterator++)
        delete iterator->second;
}
