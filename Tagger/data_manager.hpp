//
//  data_manager.hpp
//  Tagger
//
//  Created by ZhaoYuhan on 3/6/16.
//  Copyright © 2016 ZhaoYuhan. All rights reserved.
//

#ifndef data_manager_hpp
#define data_manager_hpp

#include <cstdio>
#include <functional>

#include "word.hpp"
#include "sentence.hpp"

namespace {
    const static size_t BUFFER_SIZE = 2048;
}

class DataManager
{
private:
    size_t bufferSize;

    int bufferIndex = 0;

    int bufferEnd = 0;

    char* buffer = nullptr;

    FILE* file = nullptr;

    void construct(size_t bufferSize);

    bool openFile(const char* filePath, bool read);

    bool reloadBuffer();

    char* readLine();

public:

    long readPOSFile(const char* filePath, const std::function<void (Sentence*)> placementFunction);

    DataManager() { construct(BUFFER_SIZE); }

    DataManager(size_t bufferSize) { construct(bufferSize); }
    
    ~DataManager() { delete[] buffer; }
};

#endif /* data_manager_hpp */
