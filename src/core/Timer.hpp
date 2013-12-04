#ifndef TIMER_H
#define TIMER_H

#include <sys/time.h>

namespace tigre
{
    namespace core
    {
        class Timer
        {
            public:

                Timer();

                float start();

                float tick();

                float getTime();

            private:

                struct timeval _start;

        };
    }
}

#endif
