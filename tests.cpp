// test, thus no comment
#include <windows.h>
#ifdef max
#undef max
#endif
#ifdef min
#undef min
#endif

#include <iostream>
#include <algorithm>
#include <vector>
#include <cstdint>
#include <cstdio>
#include <cstring>
#include "geometry.h"
#include "draw.h"
#include "io.h"

Vec3f v3f[] = {Vec3f(), Vec3f(1.1f, 1.1f, -3.f), Vec3f(1.1f, 2.2f, -3.f), Vec3f(2.2f, 2.2f, -3.f), Vec3f(2.2f, 1.1f, -3.f)};
Vec2f v2f[] = {Vec2f(), Vec2f(1.1f,1.1f), Vec2f(0.5f), Vec2f(3.f, 4.f)};

const int width{1920}, height{1080};
const char* modelName = "models/low-poly-female.obj";
Vec3f white(255, 255, 255);
std::vector<Vec3f> image((width)*(height));
std::vector<Triangle> faces;
std::vector<uint8_t> bMap;
HBITMAP hBitmap;

template<typename vecType0, typename vecType1, typename returnType>
inline void compute(const vecType0& v0, const vecType1& v1,
                    returnType (vecType0::*opr)(const vecType1&) const, const char* oprSym) {
    std::cout << "\n" << v0 << " " << oprSym << " " << v1 << " = " << (v0.*opr)(v1);
}

void testConstructor() {
    std::cout << "v30 by default is " << v3f[0]
            << "\nv31 is " << v3f[1]
            << "\nv32 is " << v3f[2]
            << "\nv20 by default is " << v2f[0]
            << "\nv21 is " << v2f[1]
            << "\nv22 is " << v2f[2];
}
/*
void testComputation() {
    for(int i=0; i<sizeof(v3f)/sizeof(v3f[0]) - 1; i++) {
        compute(v3f[i], v3f[i+1], &Vec3f::operator+, "+");
        compute(v3f[i], v3f[i+1], &Vec3f::operator-, "-");
        compute(v3f[i], v3f[i+1], &Vec3f::operator*, "*");
        compute(v3f[i], v3f[i+1], &Vec3f::operator^, "^");
        compute(v3f[i], 0.5f, &Vec3f::operator*, "*");
        std::cout << "\n";

        compute(v2f[i], v2f[i+1], &Vec2f::operator+, "+");
        compute(v2f[i], v2f[i+1], &Vec2f::operator-, "-");
        compute(v2f[i], v2f[i+1], &Vec2f::operator*, "*");
        compute(v2f[i], v2f[i+1], &Vec2f::operator^, "^");
        compute(v2f[i], 0.5f, &Vec2f::operator*, "*");
        std::cout << "\n";
    }
}*/

void testNorm() {
    for(int i=0; i<sizeof(v3f)/sizeof(v3f[0]); i++) {
        std::cout << "\n" << v3f[i] << " norm = " << v3f[i].norm();
        v3f[i].normalize();
        std::cout << ", " << v3f[i] << " normalized norm = " << v3f[i].norm();

        std::cout << "\n" << v2f[i] << " norm = " << v2f[i].norm();
        v2f[i].normalize();
        std::cout << ", " << v2f[i] << " normalized norm = " << v2f[i].norm();
    }
}

void testFFMatrix() {
    float elems[16] = {1.2f, 2.3f, 3.4f, 4.5f,
                       5.f, 6.f, 7.f, 8.f,
                       9.f, 10.f, 11.f, 12.f,
                       2.f, 2.f, 2.f, 2.f};
    FourFourMatrix ffmtxs[] = {FourFourMatrix(), FourFourMatrix(elems)};
    //std::cout << ffmtxs[0] << ffmtxs[1] << ffmtxs[0]*ffmtxs[1] << ffmtxs[1]*ffmtxs[1];
    for(int i=0; i<sizeof(v3f)/sizeof(v3f[0]); i++) {
        std::cout << "\n" << ffmtxs[1] << " * " << v3f[i] << " = " << ffmtxs[1].pointMul(v3f[i]);
    }
}

void testTTMatrix() {
    float elems[4] = {0.5f, 2.2f, 3.f, 4.1f};
    TwoTwoMatrix mtxs[] = {TwoTwoMatrix(), TwoTwoMatrix(elems)};
    for(int i=0; i<sizeof(v3f)/sizeof(v3f[0]); i++) {
        std::cout << "\n" << mtxs[1] << " * " << v2f[i] << " = " << mtxs[1].pointMul(v2f[i]);
    }
}

void testWireTriangle() {
    const int width{400}, height{400}, x0(200), y0(200), x1(210), y1(200), x2(205), y2(205);
    int xmin = std::min({x0, x1, x2});
    int ymin = std::min({y0, y1, y2});
    int xmax = std::max({x0, x1, x2});
    int ymax = std::max({y0, y1, y2});
    Vec3i white(255, 255, 255);
    Vec2i v0(x0, y0), v1(x1, y1), v2(x2, y2);
    wireTriangle(v0, v1, v2, image, width, height);
    for (int i=ymin; i<=ymax; i++) {
        std::cout << "\n";
        for (int j=xmin; j<=xmax; j++) {
            std::cout << image[i*width+j] << " ";
        }
    }
}

void testSaveToFile() {
    const int x0(100), y0(100), x1(300), y1(100), x2(200), y2(300);
    //for (int i=0; i<100; i++) {std::cout << image[i] << "\n";}
    Vec2i v0(x0, y0), v1(x1, y1), v2(x2, y2);
    wireTriangle(v0, v1, v2, image, width, height);
    saveToFile(image, width, height);
}

/*void drawRectangle(const Rectangle& rec) {
    Triangle t0(rec.tri0), t1(rec.tri1);
    renderTriangle(t0.ver0, t0.ver1, t0.ver2, image, width, height);
    renderTriangle(t1.ver0, t1.ver1, t1.ver2, image, width, height);
    //saveToFile(image, width, height);
}

void testPrimitive() {
    Vec3f recVertices[] = {Vec3f(0.f, 1.f, -2.f), Vec3f(2.f, 1.f, -4.f), Vec3f(0.f, 1.f, -6.f), Vec3f(-2.f, 1.f, -4.f),
                            Vec3f(0.f, -1.f, -2.f), Vec3f(2.f, -1.f, -4.f), Vec3f(0.f, -1.f, -6.f), Vec3f(-2.f, -1.f, -4.f)};
    
    Rectangle cube[6];
    cube[0] = Rectangle(recVertices[0], recVertices[1], recVertices[2], recVertices[3]);
    cube[1] = Rectangle(recVertices[4], recVertices[5], recVertices[6], recVertices[7]);
    for (int i=0; i<4; i++) {
        cube[i+2] = Rectangle(recVertices[i], recVertices[i+4], recVertices[4 + (i+5) % 4], recVertices[i+1]); 
    }
    for (int i=0; i<6; i++){
        std::cout << "\ndrawing rectangle " << i;
        drawRectangle(cube[i]);
    }

    saveToFile(image, width, height);
}*/

void testModelLoading() {
    const char* fileName = "models/low-poly-female.obj";
    std::vector<Triangle> faces;
    loadModel(fileName, faces);
    
    for (int i=0; i<faces.size(); i++) {
        Triangle tri = faces[i];
        renderTriangle(tri.ver0, tri.ver1, tri.ver2, image, width, height);
    }

    saveToFile(image, width, height);
}

/*
int main(int argc, char** argv) {
    //test vector constructor
    //testConstructor();

    //test vector computation
    //testComputation();
    
    //test normalization
    //testNorm();

    //test four by four matrix
    //testFFMatrix();

    //test two by two matrix
    //testTTMatrix();

    //test draw triangle
    //testWireTriangle();
    
    //test save to file
    //testSaveToFile();

    //test projection and wire drawing
    //renderTriangle(v3f[1], v3f[2], v3f[3], image, width, height);
    //saveToFile(image, width, height);

    //test primitive rectangle
    //testPrimitive();

    //test model loading
    const char* fileName = "models/low-poly-female.obj";
    std::vector<Triangle> faces;
    loadModel(fileName, faces);
    while (true) {
        for (int i=0; i<faces.size(); i++) {
            Triangle tri = faces[i];
            renderTriangle(tri.ver0, tri.ver1, tri.ver2, image, width, height);
        }

        std::vector<uint8_t> bMap;
        //bMap.reserve(image.size()*3);
        for (int i=0; i<image.size(); i++) {
            bMap.push_back(static_cast<uint8_t>(image[i].x));
            bMap.push_back(static_cast<uint8_t>(image[i].y));
            bMap.push_back(static_cast<uint8_t>(image[i].z));
        }
        displayRGBBuffer(bMap, width, height);
    Sleep(5000);
    }

    return 0;    
}*/

void createBitmapFromBuffer(HDC hdc, int width, int height) {
    BITMAPINFO bmi = {};

    bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
    bmi.bmiHeader.biWidth = width;
    bmi.bmiHeader.biHeight = -height;
    bmi.bmiHeader.biPlanes = 1;
    bmi.bmiHeader.biBitCount = 24;
    bmi.bmiHeader.biCompression = BI_RGB;

    void *bits;
    hBitmap = CreateDIBSection(hdc, &bmi, DIB_RGB_COLORS, &bits, NULL, 0);

    memcpy(bits, bMap.data(), bMap.size());
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch (msg) {
        case WM_PAINT: {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hwnd, &ps);
            HDC hdcMem = CreateCompatibleDC(hdc);

            DeleteObject(hBitmap);
            createBitmapFromBuffer(hdcMem, width, height);
            HBITMAP preBitmap = (HBITMAP)SelectObject(hdcMem, hBitmap);

            BitBlt(hdc, 0, 0, width, height, hdcMem, 0, 0, SRCCOPY);
            SelectObject(hdcMem, preBitmap);
            DeleteDC(hdcMem);
            EndPaint(hwnd, &ps);
            break;
        }
        case WM_DESTROY: {
            DeleteObject(hBitmap);
            PostQuitMessage(0);
            break;
        }
        case WM_TIMER: {
            InvalidateRect(hwnd, NULL, TRUE);
            break;
        }
        case WM_KEYDOWN: {
            switch (wParam) {
                case VK_UP: {
                    Vec3f step{0.f, -1.f, 0.f};
                    std::cout << "\nUp pressed\n";
                    memset(&image[0], 0, image.size()*sizeof(Vec3f));
                    for (int i=0; i<faces.size(); i++) {
                        renderTriangle(faces[i].ver0+step, faces[i].ver1+step, faces[i].ver2+step, image, width, height);
                    }

                //bMap.reserve(image.size()*3);
                    bMap.clear();
                    for (int i=0; i<image.size(); i++) {
                        bMap.push_back(static_cast<uint8_t>(image[i].x));
                        bMap.push_back(static_cast<uint8_t>(image[i].y));
                        bMap.push_back(static_cast<uint8_t>(image[i].z));
                    }
                    
                    InvalidateRect(hwnd, NULL, TRUE);
                    UpdateWindow(hwnd);
                    break;
                }
                case VK_DOWN: {
                    Vec3f step{0.f, 1.f, 0.f};
                    std::cout << "\nDown pressed\n";
                    memset(&image[0], 0, image.size()*sizeof(Vec3f));
                    for (int i=0; i<faces.size(); i++) {
                        renderTriangle(faces[i].ver0+step, faces[i].ver1+step, faces[i].ver2+step, image, width, height);
                    }

                //bMap.reserve(image.size()*3);
                    bMap.clear();
                    for (int i=0; i<image.size(); i++) {
                        bMap.push_back(static_cast<uint8_t>(image[i].x));
                        bMap.push_back(static_cast<uint8_t>(image[i].y));
                        bMap.push_back(static_cast<uint8_t>(image[i].z));
                    }
                    
                    InvalidateRect(hwnd, NULL, TRUE);
                    UpdateWindow(hwnd);
                    break;
                }
                case 0x57: {
                    Vec3f step{0.f, 0.f, 1.f};
                    std::cout << "\nW pressed\n";
                    memset(&image[0], 0, image.size()*sizeof(Vec3f));
                    for (int i=0; i<faces.size(); i++) {
                        renderTriangle(faces[i].ver0+step, faces[i].ver1+step, faces[i].ver2+step, image, width, height);
                    }

                //bMap.reserve(image.size()*3);
                    bMap.clear();
                    for (int i=0; i<image.size(); i++) {
                        bMap.push_back(static_cast<uint8_t>(image[i].x));
                        bMap.push_back(static_cast<uint8_t>(image[i].y));
                        bMap.push_back(static_cast<uint8_t>(image[i].z));
                    }
                    
                    InvalidateRect(hwnd, NULL, TRUE);
                    UpdateWindow(hwnd);
                    break;
                }
                case 0x53: {
                    Vec3f step{0.f, 0.f, -1.f};
                    std::cout << "\nS pressed\n";
                    memset(&image[0], 0, image.size()*sizeof(Vec3f));
                    for (int i=0; i<faces.size(); i++) {
                        renderTriangle(faces[i].ver0+step, faces[i].ver1+step, faces[i].ver2+step, image, width, height);
                    }

                //bMap.reserve(image.size()*3);
                    bMap.clear();
                    for (int i=0; i<image.size(); i++) {
                        bMap.push_back(static_cast<uint8_t>(image[i].x));
                        bMap.push_back(static_cast<uint8_t>(image[i].y));
                        bMap.push_back(static_cast<uint8_t>(image[i].z));
                    }
                    
                    InvalidateRect(hwnd, NULL, TRUE);
                    UpdateWindow(hwnd);
                    break;
                }
                case 0x41: {
                    Vec3f step{1.f, 0.f, -0.f};
                    std::cout << "\nA pressed\n";
                    memset(&image[0], 0, image.size()*sizeof(Vec3f));
                    for (int i=0; i<faces.size(); i++) {
                        renderTriangle(faces[i].ver0+step, faces[i].ver1+step, faces[i].ver2+step, image, width, height);
                    }

                //bMap.reserve(image.size()*3);
                    bMap.clear();
                    for (int i=0; i<image.size(); i++) {
                        bMap.push_back(static_cast<uint8_t>(image[i].x));
                        bMap.push_back(static_cast<uint8_t>(image[i].y));
                        bMap.push_back(static_cast<uint8_t>(image[i].z));
                    }
                    
                    InvalidateRect(hwnd, NULL, TRUE);
                    UpdateWindow(hwnd);
                    break;
                }
                case 0x44: {
                    Vec3f step{-1.f, 0.f, 0.f};
                    std::cout << "\nD pressed\n";
                    memset(&image[0], 0, image.size()*sizeof(Vec3f));
                    for (int i=0; i<faces.size(); i++) {
                        renderTriangle(faces[i].ver0+step, faces[i].ver1+step, faces[i].ver2+step, image, width, height);
                    }

                //bMap.reserve(image.size()*3);
                    bMap.clear();
                    for (int i=0; i<image.size(); i++) {
                        bMap.push_back(static_cast<uint8_t>(image[i].x));
                        bMap.push_back(static_cast<uint8_t>(image[i].y));
                        bMap.push_back(static_cast<uint8_t>(image[i].z));
                    }
                    
                    InvalidateRect(hwnd, NULL, TRUE);
                    UpdateWindow(hwnd);
                    break;
                }
            }
            break;
        }
        default: {
            return DefWindowProc(hwnd, msg, wParam, lParam);
        }
    }

    return 0;
}

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hInstPrev, PSTR cmdline, int cmdshow) {
    WNDCLASS wc = {};
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = "renderer";

    RegisterClass(&wc);

    HWND hwnd = CreateWindowEx(0, "renderer", "renderer window", WS_OVERLAPPEDWINDOW,
                               0, 0, width, height, NULL, NULL, hInstance, NULL);
    ShowWindow(hwnd, cmdshow);

    // load model
    loadModel(modelName, faces);
    for (int i=0; i<faces.size(); i++) {
            Triangle tri = faces[i];
            renderTriangle(tri.ver0, tri.ver1, tri.ver2, image, width, height);
    }

    //bMap.reserve(image.size()*3);
    for (int i=0; i<image.size(); i++) {
        bMap.push_back(static_cast<uint8_t>(image[i].x));
        bMap.push_back(static_cast<uint8_t>(image[i].y));
        bMap.push_back(static_cast<uint8_t>(image[i].z));
    }

    // Create the bitmap once at the beginning
    HDC hdc = GetDC(hwnd);
    createBitmapFromBuffer(hdc, width, height);
    ReleaseDC(hwnd, hdc);

    //SetTimer(hwnd, 0, 1000, NULL);

    // Main message loop
    MSG msg = {};
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}
