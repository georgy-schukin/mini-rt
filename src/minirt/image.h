#pragma once

#include "color.h"

#include <vector>
#include <string>

namespace minirt {

class Image {
public:
    Image();
    Image(int width, int height);

    int getWidth() const;
    int getHeight() const;

    void set(int x, int y, const Color &color);
    const Color& get(int x, int y) const;

    void saveJPEG(const std::string &filename, int quality = 90);

private:
    std::vector<Color> data;
    int width;
    int height;
};

}
