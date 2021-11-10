#pragma once

namespace minirt {

struct Color {
    double red;
    double green;
    double blue;

    Color();
    Color(double r, double g, double b);
    Color(double c);

    void operator +=(const Color &c);
};

Color operator +(const Color &c1, const Color &c2);
Color operator -(const Color &c1, const Color &c2);
Color operator *(const Color &c1, const Color &c2);
Color operator *(const Color &c, double coeff);
Color operator *(double coeff, const Color &c);

}
