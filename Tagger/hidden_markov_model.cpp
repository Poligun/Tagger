//
//  hidden_markov_model.cpp
//  Tagger
//
//  Created by ZhaoYuhan on 3/6/16.
//  Copyright © 2016 ZhaoYuhan. All rights reserved.
//

#include "hidden_markov_model.hpp"

#include <cstdio>

using namespace std;

void HiddenMarkovModel::construct(int order, bool caseSensitive)
{
    this->order = order;
    this->caseSensitive = caseSensitive;

    startStateNames = new string[order];
    for (int i = 0; i < order; i++) {
        startStateNames[i] = "Start-" + to_string(i + 1);
        stateMap[startStateNames[i]] = make_shared<State>(startStateNames[i]);
    }

    stateMap[endStateName] = make_shared<State>(endStateName);
    stateMap[endStateName]->addEmission(endWord);
}

HiddenMarkovModel::~HiddenMarkovModel()
{
    delete[] startStateNames;
}

void HiddenMarkovModel::addSentence(const Sentence& sentence)
{
    auto stateNameSize = sentence.numberOfWords() + order + 1;
    auto stateNames = new const string*[stateNameSize];

    for (int i = 0; i < order; i++)
        stateNames[i] = &startStateNames[i];

    int index = order;

    for (auto& word : sentence.getWords()) {
        shared_ptr<State> state;
        string stateName;

        if (caseSensitive && isCapitalized(word->getWord()))
            stateName = State::Capitalize(word->getTag());
        else
            stateName = word->getTag();

        if (stateMap.find(stateName) == stateMap.end())
            stateMap[stateName] = make_shared<State>(stateName, word->getTag());

        state = stateMap[stateName];
        stateNames[index++] = &state->getName();

        state->addEmission(word->getWord());
    }

    stateNames[index] = &endStateName;
    stateMap[endStateName]->addEmission(endWord);

    for (int i = 0; i < stateNameSize; i++)
        rootTransition.addTransition(nullptr, 0, *stateNames[i]);

    for (int i = 1; i <= order; i++) {
        for (int j = i; j < stateNameSize; j++)
            rootTransition.addTransition(&stateNames[j - i], i, *stateNames[j]);
    }

    delete[] stateNames;
}
