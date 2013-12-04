#include "Timer.hpp"

namespace tigre
{
    namespace core
    {
        Timer::Timer()
        {
        }

        float Timer::start()
        {
            gettimeofday(&_start, 0);
            return 0.0f;
        }

        float Timer::tick()
        {
            float time = getTime();
            start();
            return time;
        }

        float getElapsedTime(struct timeval t1, struct timeval t2)
        {
            return t2.tv_sec - t1.tv_sec + (float)(t2.tv_usec - t1.tv_usec) / 1000000;
        }

        float Timer::getTime()
        {
            struct timeval now;
            gettimeofday(&now, 0);
            return getElapsedTime(_start, now);
        }
    }
}
