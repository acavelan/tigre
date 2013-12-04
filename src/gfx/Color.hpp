#ifndef COLOR_H
#define COLOR_H

namespace tigre
{
    namespace gfx
    {
        class Color
        {
            public:

                Color();
                explicit Color(float red, float green, float blue, float alpha = 1.0f);

                float r, g, b, a;
        };

        namespace color
        {
            extern const Color White;
            extern const Color Black;
            extern const Color Red;
            extern const Color Green;
            extern const Color Blue;
            extern const Color Yellow;
        }
    }
}

#endif
