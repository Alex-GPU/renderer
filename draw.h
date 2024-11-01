#ifndef DRAW_H
#define DRAE_H

#include <vector>
#include "geometry.h"

void drawLine(const Vec2i&, const Vec2i&, std::vector<Vec3f>&, int, int, const Vec3f& color=Vec3f(255,255,255));
void wireTriangle(const Vec2i&, const Vec2i&, const Vec2i&, std::vector<Vec3f>&, int, int, const Vec3f& color=Vec3f(255,255,255));
void renderTriangle(const Vec3f&, const Vec3f&, const Vec3f&, std::vector<Vec3f>&, int, int, const Vec3f& color=Vec3f(255,255,255));

#endif
