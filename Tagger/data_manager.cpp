//
//  data_manager.cpp
//  Tagger
//
//  Created by ZhaoYuhan on 3/6/16.
//  Copyright © 2016 ZhaoYuhan. All rights reserved.
//

#include "data_manager.hpp"
#include <cstring>

void DataManager::construct(size_t bufferSize)
{
    this->bufferSize = bufferSize;
    buffer = new char[bufferSize + 1];
}

bool DataManager::openFile(const char* filePath, bool read)
{
    file = fopen(filePath, read ? "rb" : "wb");
    return file;
}

bool DataManager::reloadBuffer()
{
    if (bufferIndex < bufferEnd) {
        auto reservedSize = bufferEnd - bufferIndex;
        memcpy(buffer, buffer + bufferIndex, sizeof(char) * reservedSize);
        bufferEnd = reservedSize;
    }
    else {
        bufferEnd = 0;
    }

    if (!file)
        return false;

    auto itemsRead = fread(buffer + bufferEnd, sizeof(char), bufferSize - bufferEnd, file);

    bufferIndex = 0;
    bufferEnd += itemsRead;

    if (itemsRead == 0) {
        fclose(file);
        file = nullptr;
    }

    return itemsRead > 0;
}

char* DataManager::readLine()
{
    if (bufferIndex >= bufferEnd)
        reloadBuffer();

    while (true) {
        for (auto i = bufferIndex; i < bufferEnd; i++) {
            if (buffer[i] == '\r') {
                buffer[i] = '\0';
            }
            else if (buffer[i] == '\n') {
                buffer[i] = '\0';
                auto line = buffer + bufferIndex;
                bufferIndex = i + 1;
                return line;
            }
        }
        if (!reloadBuffer()) {
            if (bufferIndex >= bufferEnd)
                return nullptr;
            buffer[bufferEnd] = '\0';
            auto line = buffer + bufferIndex;
            bufferIndex = bufferEnd;
            return line;
        }
    }
}

long DataManager::readPOSFile(const char* filePath, const std::function<void (Sentence*)> placementFunction)
{
    Sentence *sentence = nullptr;
    long counter = 0;
    decltype(readLine()) line = nullptr;

    if (openFile(filePath, true)) {
        while ((line = readLine()) != nullptr) {
            if (strlen(line) == 0) {
                if (sentence) {
                    placementFunction(sentence);
                    sentence = nullptr;
                }
                continue;
            }

            auto indexOfTab = line;

            for (; *indexOfTab != '\0'; indexOfTab++) {
                if (*indexOfTab == '\t') {
                    *(indexOfTab++) = '\0';
                    break;
                }
            }

            if (!sentence)
                sentence = new Sentence();

            sentence->addWord(line, indexOfTab);
        }
    }

    return counter;
}
