//
//  word.hpp
//  Tagger
//
//  Created by ZhaoYuhan on 3/6/16.
//  Copyright © 2016 ZhaoYuhan. All rights reserved.
//

#ifndef word_hpp
#define word_hpp

#include <cstring>
#include <string>
#include <vector>
#include <memory>

#include <iostream>

namespace {
    const static size_t DEFAULT_STRING_SIZE = 100;
}

class Word
{
private:
    size_t wordStringSize = DEFAULT_STRING_SIZE;

    char* word = new char[DEFAULT_STRING_SIZE];

    std::string tag;

public:

    const decltype(word) getWord() const { return word; }

    const std::string& getTag() const { return tag; }

    void setWord(const char* word)
    {
        auto stringLength = strlen(word);

        if (stringLength > wordStringSize) {
            delete[] word;
            this->word = new char[stringLength];
            wordStringSize = stringLength;
        }

        strcpy(this->word, word);
    }

    void setTag(const char* tag)
    {
        this->tag = std::string(tag);
    }

    Word() {}

    Word(const char* word, const char* tag)
    {
        setWord(word);
        setTag(tag);
    }

    Word(const Word& word)
    {
        this->word = new char[strlen(word.word) + 1];
        strcpy(this->word, word.word);
        this->tag = word.tag;
    }

    ~Word()
    {
        if (word) {
            delete[] word;
            word = nullptr;
        }
    }
};

#endif /* word_hpp */
