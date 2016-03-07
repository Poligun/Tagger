//
//  transition.hpp
//  Tagger
//
//  Created by ZhaoYuhan on 3/6/16.
//  Copyright © 2016 ZhaoYuhan. All rights reserved.
//

#ifndef transition_hpp
#define transition_hpp

#include <string>
#include <unordered_map>

class Transition
{
private:
    std::unordered_map<std::string, Transition*> transitionMap;

    int sumOfFrequencies = 0;

    std::unordered_map<std::string, int> stateFrequencies;

public:

    Transition& getTransition(const std::string* stateNames[], int size);

    const Transition& getTransition(const std::string* stateNames[], int size) const;

    void addTransition(const std::string* stateNames[], int size, const std::string& targetStateName);

    ~Transition();
};

#endif /* transition_hpp */
