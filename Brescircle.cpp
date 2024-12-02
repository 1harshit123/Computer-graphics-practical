#include <iostream>
#include <graphics.h>
#include <cmath>
using namespace std;

void BresenhamCircle(int r, int xShift, int yShift, int scale) {
    int x = 0;
    int y = r;
    int d = 1 - r;

    while (y >= x) {
        // Plot all eight symmetrical points
        putpixel((xShift + x) * scale, (yShift + y) * scale, GREEN);
        putpixel((xShift - x) * scale, (yShift + y) * scale, GREEN);
        putpixel((xShift + x) * scale, (yShift - y) * scale, GREEN);
        putpixel((xShift - x) * scale, (yShift - y) * scale, GREEN);
        putpixel((xShift + y) * scale, (yShift + x) * scale, GREEN);
        putpixel((xShift - y) * scale, (yShift + x) * scale, GREEN);
        putpixel((xShift + y) * scale, (yShift - x) * scale, GREEN);
        putpixel((xShift - y) * scale, (yShift - x) * scale, GREEN);

        if (d < 0) {
            d += 2 * x + 3;
        } else {
            d += 2 * (x - y) + 5;
            y--;
        }
        x++;
    }
}

int main() {
    int r = 200;
    int xShift = 600, yShift = 300, scale = 1;

    int gd = DETECT, gm;
    int screenWidth = GetSystemMetrics(SM_CXSCREEN);
    int screenHeight = GetSystemMetrics(SM_CYSCREEN);
    initwindow(screenWidth, screenHeight, "Full Size BGI Window");

    BresenhamCircle(r, xShift, yShift, scale);

    getch();
    closegraph();

    return 0;
}
