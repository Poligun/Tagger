//
//  timer.hpp
//  Tagger
//
//  Created by ZhaoYuhan on 3/6/16.
//  Copyright © 2016 ZhaoYuhan. All rights reserved.
//

#ifndef timer_hpp
#define timer_hpp

#include <vector>
#include <chrono>

class Timer
{
private:
    std::vector<decltype(std::chrono::system_clock::now())> timeStamps;

public:
    void tick() { timeStamps.push_back(std::chrono::system_clock::now()); }

    long lastDuration() const
    {
        if (timeStamps.size() < 2)
            return 0;

        const auto& t2 = timeStamps.back();
        const auto& t1 = timeStamps[timeStamps.size() - 2];
        const auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1);

        return duration.count();
    }

    long totalDuration() const
    {
        if (timeStamps.size() < 2)
            return 0;
        else
            return std::chrono::duration_cast<std::chrono::milliseconds>(timeStamps.back() - timeStamps.front()).count();
    }
};

#endif /* timer_hpp */
