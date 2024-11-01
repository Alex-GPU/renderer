#include <algorithm>
#include "draw.h"
#include "geometry.h"

// uses error accumulation optmization
void drawLine(const Vec2i& v0, const Vec2i& v1, std::vector<Vec3f>& image,
                int width, int height, const Vec3f& color) {
    //std::cout << "\n\t\t drawing line between " << v0 << " and " << v1;
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
        if (steep) {
            if ((x*width + y) < width*height && (x*width + y) >= 0) {
                image[x*width + y] = color;
            }
        }
        else {
            if ((y*width + x) < width*height && (y*width + x) >= 0) {
                image[y*width + x] = color;
            }
        }

        error += dy;
        if (error > 0.5f) {
            error -= 1.f;
            y += step;
        }
    }
}

// draw lines among v0, v1, v2
void wireTriangle(const Vec2i& v0, const Vec2i& v1, const Vec2i& v2, std::vector<Vec3f>& image,
                    int width, int height, const Vec3f& color) {
    //std::cout << "\n\t wiring 2D triangle " << v0 << v1 << v2;
    drawLine(v0, v1, image, width, height);
    drawLine(v1, v2, image, width, height);
    drawLine(v2, v0, image, width, height);
}

Vec2f projection(const Vec3f& point, float zNear=-1.f) {
    return Vec2f(point.x*zNear/point.z, point.y*zNear/point.z);
}

// project v0, v1, v2 then draw wire triangle, screen size 2 by 2
void renderTriangle(const Vec3f& v0, const Vec3f& v1, const Vec3f& v2, std::vector<Vec3f>& image, 
                    int width, int height, const Vec3f& color) {
    //std::cout << "\nrender triangle " << v0 << v1 << v2;
    Vec2f pV0 = projection(v0);
    Vec2f pV1 = projection(v1);
    Vec2f pV2 = projection(v2);

    float deviceRatio = (float)width/(float)height;

    // calculate pixel coordinates in image
    Vec2i sV0 = Vec2i((int)((float)width*(pV0.x/deviceRatio+1.f)/2.f), (int)((float)height*(1.f-pV0.y)/2.f));
    Vec2i sV1 = Vec2i((int)((float)width*(pV1.x/deviceRatio+1.f)/2.f), (int)((float)height*(1.f-pV1.y)/2.f));
    Vec2i sV2 = Vec2i((int)((float)width*(pV2.x/deviceRatio+1.f)/2.f), (int)((float)height*(1.f-pV2.y)/2.f));

    wireTriangle(sV0, sV1, sV2, image, width, height, color);
}
