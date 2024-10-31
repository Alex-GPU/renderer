#ifndef DRAW_H
#define DRAE_H

#include "geometry.h"

void drawLine(const Vec2i&, const Vec2i&, Vec3i[], int, int, const Vec3i& color=Vec3i(255, 255, 255));
void wireTriangle(const Vec2i&, const Vec2i&, const Vec2i&, Vec3i[], int, int, const Vec3i& color=Vec3i(255, 255, 255));

#endif
