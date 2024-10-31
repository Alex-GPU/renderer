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
        if (steep) {if ((x*width + y) < width*height) image[x*width + y] = color;}
        else {if ((y*width + x) < width*height) image[y*width + x] = color;}

        error += dy;
        if (error > 0.5f) {
            error -= 1.f;
            y += step;
        }
    }
}

// draw lines among v0, v1, v2
void wireTriangle(const Vec2i& v0, const Vec2i& v1, const Vec2i& v2, Vec3i image[],
                    int width, int height, const Vec3i& color) {
    drawLine(v0, v1, image, width, height);
    drawLine(v1, v2, image, width, height);
    drawLine(v2, v0, image, width, height);
}

Vec2f projection(const Vec3f& point, int zNear=-1) {
    return Vec2f(point.x*(float)zNear/point.z, point.y*(float)zNear/point.z);
}

// project v0, v1, v2 then draw wire triangle, screen size 2 by 2
void renderTriangle(const Vec3f& v0, const Vec3f& v1, const Vec3f& v2, Vec3i image[], 
                    int width, int height, const Vec3i& color) {
    Vec2f pV0 = projection(v0);
    Vec2f pV1 = projection(v1);
    Vec2f pV2 = projection(v2);

    // calculate pixel coordinates in image
    Vec2i sV0 = Vec2i((int)((float)width*(pV0.x+1.f)/2.f), (int)((float)height*(1.f-pV0.y)/2.f));
    Vec2i sV1 = Vec2i((int)((float)width*(pV1.x+1.f)/2.f), (int)((float)height*(1.f-pV1.y)/2.f));
    Vec2i sV2 = Vec2i((int)((float)width*(pV2.x+1.f)/2.f), (int)((float)height*(1.f-pV2.y)/2.f));

    wireTriangle(sV0, sV1, sV2, image, width, height, color);
}
