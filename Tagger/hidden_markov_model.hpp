//
//  hidden_markov_model.hpp
//  Tagger
//
//  Created by ZhaoYuhan on 3/6/16.
//  Copyright © 2016 ZhaoYuhan. All rights reserved.
//

#ifndef hidden_markov_model_hpp
#define hidden_markov_model_hpp

#include <string>
#include <vector>
#include <unordered_map>
#include <memory>
#include <functional>

#include "sentence.hpp"
#include "state.hpp"
#include "transition.hpp"

class HiddenMarkovModel
{
private:
    int order;

    bool caseSensitive;

    std::string* startStateNames = nullptr;

    std::string endStateName = "End";

    std::string endWord = "$#End-Word#$";

    std::unordered_map<std::string, std::shared_ptr<State>> stateMap;

    std::function<bool(const std::string&)> isCapitalized = [](const std::string& word) {
        return word.length() && 'A' <= word.front() && word.front() <= 'Z';
    };;

    Transition rootTransition;

    void construct(int order, bool caseSensitive);

public:

    void addSentence(const Sentence& sentence);

    HiddenMarkovModel() { construct(0, false); }

    HiddenMarkovModel(int order) { construct(order, false); }

    HiddenMarkovModel(int order, bool caseSensitive) { construct(order, caseSensitive); }

    ~HiddenMarkovModel();
};

#endif /* hidden_markov_model_hpp */
