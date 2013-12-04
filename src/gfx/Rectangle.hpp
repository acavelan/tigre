#ifndef RECTANGLE_H
#define RECTANGLE_H

namespace tigre
{
    namespace gfx
    {
        class Rectangle
        {
            public:

                Rectangle(int x, int y, int width, int height);

                int x, y;
                int width, height;

        };
    }
}

#endif
