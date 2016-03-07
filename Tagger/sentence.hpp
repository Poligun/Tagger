//
//  sentence.hpp
//  Tagger
//
//  Created by ZhaoYuhan on 3/6/16.
//  Copyright © 2016 ZhaoYuhan. All rights reserved.
//

#ifndef sentence_hpp
#define sentence_hpp

#include <vector>
#include <memory>

#include "word.hpp"

class Sentence
{
private:
    std::vector<std::unique_ptr<Word>> words;

public:

    const decltype(words)& getWords() const { return words; }

    const size_t numberOfWords() const { return words.size(); }

    void addWord(const char* word, const char* tag)
    {
        words.emplace_back(new Word(word, tag));
    }
};

#endif /* sentence_hpp */
