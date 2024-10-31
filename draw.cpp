#include <algorithm>
#include "draw.h"
#include "geometry.h"

// uses error accumulation optmization
void drawLine(const Vec2i& v0, const Vec2i& v1, Vec3i image[],
                int width, int height, const Vec3i& color) {
    int x0(v0.x), y0(v0.y), x1(v1.x), y1(v1.y);

    bool steep = false;
    if (std::abs(y1-y0) > std::abs(x1-x0)) {
        steep = true;
        std::swap(x0, y0);
        std::swap(x1, y1);
    }

    if (x0 > x1) {
        std::swap(x0, x1);
        std::swap(y0, y1);
    }

    float dy = (float)(y1-y0) / (float)(x1-x0);
    float error(0), step(1);
    if (dy < 0) {
        dy = -dy;
        step = -1;
    }

    int y = y0;
    for (int x=x0; x<=x1; x++) {
        if (steep) {image[x*width + y] = color;}
        else {image[y*width + x] = color;}

        error += dy;
        if (error > 0.5f) {
            error -= 1.f;
            y += step;
        }
    }
}

void wireTriangle(const Vec2i& v0, const Vec2i& v1, const Vec2i& v2, Vec3i image[],
                    int width, int height, const Vec3i& color) {
    drawLine(v0, v1, image, width, height);
    drawLine(v1, v2, image, width, height);
    drawLine(v2, v0, image, width, height);
}
