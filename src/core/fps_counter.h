//
// Created by q on 2023/10/25.
//

#ifndef MYSOFTWARERENDERPIPE_FPS_COUNTER_H
#define MYSOFTWARERENDERPIPE_FPS_COUNTER_H

#include "chrono"
#include "queue"

class fpsCounter {
public:
    std::chrono::milliseconds statisticsDuration{1000};

    /**
     * 添加要记录的一帧的时间点
     */
    void addFrame(std::chrono::time_point<std::chrono::system_clock>);

    double getFPS() const;

private:
    std::queue<std::chrono::time_point<std::chrono::system_clock>> frames;
};


#endif //MYSOFTWARERENDERPIPE_FPS_COUNTER_H
