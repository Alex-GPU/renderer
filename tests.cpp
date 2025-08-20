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

void updateFrame(HWND hwnd, Vec3f step) {
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
                    //std::cout << "\nUp pressed\n";
                    updateFrame(hwnd, step);
                    break;
                }
                case VK_DOWN: {
                    Vec3f step{0.f, 1.f, 0.f};
                    //std::cout << "\nDown pressed\n";
                    updateFrame(hwnd, step);
                    break;
                }
                case 0x57: {
                    Vec3f step{0.f, 0.f, 1.f};
                    //std::cout << "\nW pressed\n";
                    updateFrame(hwnd, step);
                    break;
                }
                case 0x53: {
                    Vec3f step{0.f, 0.f, -1.f};
                    //std::cout << "\nS pressed\n";
                    updateFrame(hwnd, step);
                    break;
                }
                case 0x41: {
                    Vec3f step{1.f, 0.f, -0.f};
                    //std::cout << "\nA pressed\n";
                    updateFrame(hwnd, step);
                    break;
                }
                case 0x44: {
                    Vec3f step{-1.f, 0.f, 0.f};
                    //std::cout << "\nD pressed\n";
                    updateFrame(hwnd, step);
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
