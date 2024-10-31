#include <fstream>
#include "io.h"

void saveToFile(Vec3i image[], int width, int height) {
    std::ofstream output("frame.ppm");
    output << "P3\n" << width << " " << height << "\n255\n";

    for(int j=0; j<height; j++) {
        for (int i=0; i<width; i++) {
            Vec3i p = image[j*width+i];
            output << p.x << " " << p.y << " " << p.z << "\t";
        }
        output << "\n";
    }

    output.close();
}
