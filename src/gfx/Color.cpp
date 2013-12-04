#include "Color.hpp"

namespace tigre
{
    namespace gfx
    {
        Color::Color() :
            r(0.0f), g(0.0f), b(0.0f), a(0.0f)
        {
        }

        Color::Color(float red, float green, float blue, float alpha) :
            r(red), g(green), b(blue), a(alpha)
        {
        }

        const Color color::White(1.0f, 1.0f, 1.0f, 1.0f);
        const Color color::Black(0.0f, 0.0f, 0.0f, 1.0f);
        const Color color::Red(1.0f, 0.0f, 0.0f, 1.0f);
        const Color color::Green(0.0f, 1.0f, 0.0f, 1.0f);
        const Color color::Blue(0.0f, 0.0f, 1.0f, 1.0f);
        const Color color::Yellow(1.0f, 1.0f, 0.0f, 1.0f);
    }
}
