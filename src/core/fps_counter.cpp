//
// Created by q on 2023/10/25.
//

#include "fps_counter.h"

void fpsCounter::addFrame(std::chrono::time_point<std::chrono::system_clock> frameTimePoint) {
    while (!frames.empty() && (frameTimePoint - frames.front()) > statisticsDuration) {
        frames.pop();
    }
    frames.push(frameTimePoint);
}

double fpsCounter::getFPS() const {
    return 1000.0 * frames.size() / statisticsDuration.count();
}
