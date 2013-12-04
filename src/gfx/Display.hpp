#ifndef DISPLAY_H
#define DISPLAY_H

/**
 * Base class for the Display
 *
 * The goal of this class is to abstract everything that concerns
 * widgets management, OpenGL or context creation.
 */

namespace tigre
{
    namespace gfx
    {
        class Display
        {
            public:

                virtual ~Display() {}

                virtual void resize(int width, int height) = 0;

                virtual int getWidth() const = 0;

                virtual int getHeight() const = 0;

        };
    }
}

#endif
