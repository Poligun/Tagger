//
//  main.cpp
//  Tagger
//
//  Created by ZhaoYuhan on 3/6/16.
//  Copyright © 2016 ZhaoYuhan. All rights reserved.
//

#include <iostream>
#include <vector>
#include <memory>

#include "timer.hpp"
#include "data_manager.hpp"
#include "hidden_markov_model.hpp"

using namespace std;

const char testingFilePath[] = "/Users/zhaoyuhan/Dropbox/Natual Language Processing/hw4/wsj/WSJ_02-21.pos";

int main(int argc, const char * argv[])
{
    Timer timer;
    DataManager dataManager;
    HiddenMarkovModel hmm;
    vector<unique_ptr<Sentence>> sentences;

    cout << "Program started..." << endl;

    timer.tick();
    dataManager.readPOSFile(testingFilePath, [&sentences](Sentence* sentence) {
        sentences.emplace_back(sentence);
    });
    timer.tick();

    cout << sentences.size() << " sentences read." << endl;

    for (auto& sentence : sentences)
        hmm.addSentence(*sentence);

    cout << "Finished within " << timer.lastDuration() << " ms." << endl;

    return 0;
}
