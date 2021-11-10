#include "color.h"

namespace minirt {

Color::Color() :
    red(0), green(0), blue(0) {
}

Color::Color(double r, double g, double b) :
    red(r), green(g), blue(b) {
}

Color::Color(double c) :
    red(c), green(c), blue(c) {
}

void Color::operator +=(const Color &c) {
    red += c.red;
    green += c.green;
    blue += c.blue;
}

Color operator +(const Color &c1, const Color &c2) {
    return Color {c1.red + c2.red, c1.green + c2.green, c1.blue + c2.blue};
}

Color operator -(const Color &c1, const Color &c2) {
    return Color {c1.red - c2.red, c1.green - c2.green, c1.blue - c2.blue};
}

Color operator *(const Color &c1, const Color &c2) {
    return Color {c1.red * c2.red, c1.green * c2.green, c1.blue * c2.blue};
}

Color operator *(const Color &c, double coeff) {
    return Color {coeff * c.red, coeff * c.green, coeff * c.blue};
}

Color operator *(double coeff, const Color &c) {
    return c * coeff;
}

}
