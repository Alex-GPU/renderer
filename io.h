#ifndef IO_H
#define IO_H

#include <vector>
#include "geometry.h"

//saves a frame to a .ppm(P3) file
void saveToFile(std::vector<Vec3f>& image, int, int);
void loadModel(const char*, std::vector<Triangle>&);

#endif
