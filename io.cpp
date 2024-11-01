#include <fstream>
#include <cstring>
#include "io.h"

void saveToFile(std::vector<Vec3f>& image, int width, int height) {
    std::ofstream output("single frame.ppm");
    output << "P3\n" << width << " " << height << "\n255\n";

    for(int j=0; j<height; j++) {
        for (int i=0; i<width; i++) {
            Vec3f p = image[j*width+i];
            output << p.x << " " << p.y << " " << p.z << "\t";
        }
        output << "\n";
    }

    output.close();
}

void getFaces(char line[], std::vector<Triangle>& faces, std::vector<Vec3f>& vertices) {
    char *sp0, *sp1, *coor;
    int nToken=0;
    Triangle tri = Triangle(Vec3f(), Vec3f(), Vec3f());

    coor = strtok_s(line+2, " ", &sp0);
    while (coor) {
        int vertLine = std::atoi(strtok_s(coor, "/", &sp1));
        if (vertLine < 0) {vertLine += vertices.size();}
        else {vertLine -= 1;}
        if (nToken > 1) {
            tri.ver2 = vertices[vertLine];
            faces.push_back(tri);
            tri.ver1 = vertices[vertLine];
        } else {tri[nToken] = vertices[vertLine];}
        std::cout << "\nlooking for line " << vertLine << " vertices size is " << vertices.size();
        coor = strtok_s(NULL, " ", &sp0);
        nToken++;
    }
}

void loadModel(const char* fName, std::vector<Triangle>& faces) {
    const int LineMax = 100;
    char line[LineMax];
    char* coor;
    std::ifstream modelFile(fName);
    std::vector<Vec3f> vertices;
    int i = 0;
    Vec3f v;
    Triangle tri(v, v, v);

    while (modelFile.getline(line, LineMax)) {
        if (line[0] == 'v' && line[1] == ' ') {
            coor = strtok(line+2, " ");
            while (coor) {
                //std::cout << std::atof(coor) << " ";
                v[i] = std::atof(coor);
                if (i==2){v[i] -= 50.f;}
                else if (i==1) {v[i] -=40.f;}
                //else {v[i] += 1700.f;}
                i++;
                coor = strtok(NULL, " ");
            }
            i=0;
            vertices.push_back(v);
            //std::cout << "\n";
        } else if (line[0] == 'f' && line[1]==' ') {
            getFaces(line, faces, vertices);
            /*char *sp0, *sp1;
            int nToken=0;
            coor = strtok_s(line+2, " ", &sp0);
            while (coor) {
                int vertLine = std::atoi(strtok_s(coor, "/", &sp1));
                if (vertLine < 0) {vertLine += vertices.size();}
                else {vertLine -= 1;}
                if (nToken > 2) {
                    Triangle quadTri(tri.ver0, tri.ver2, vertices[vertLine]);
                    faces.push_back(quadTri);
                } else {tri[i++] = vertices[vertLine];}
                std::cout << "\nlooking for line " << vertLine << " vertices size is " << vertices.size() << " i is " << i;
                coor = strtok_s(NULL, " ", &sp0);
                nToken++;
            }
            i=0;
            faces.push_back(tri);*/
        }
    }

    //for (int i=0; i<faces.size(); i++) {
    //    std::cout << faces[i] << "\n";
    //}

    modelFile.close();
}
