//
//  state.hpp
//  Tagger
//
//  Created by ZhaoYuhan on 3/6/16.
//  Copyright © 2016 ZhaoYuhan. All rights reserved.
//

#ifndef state_hpp
#define state_hpp

#include <string>
#include <unordered_map>

class State
{
private:
    std::string name;

    std::string tag;

    int sumOfFrequencies = 0;

    std::unordered_map<std::string, int> emissionFrequencies;

public:

    const std::string& getName() const { return name; }

    const std::string& getTag() const { return tag; }

    void addEmission(const std::string& word);

    State(const std::string& name) : name(name), tag(name) {}

    State(const std::string& name, const std::string& tag) : name(name), tag(tag) {}

    static const std::string Capitalize(const std::string& stateName) { return stateName + "-Capital"; }
};

#endif /* state_hpp */
