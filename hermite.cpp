#include <graphics.h>
#include <iostream>
#include <cmath>
using namespace std;

void drawHermite(int x0, int y0, int x1, int y1, int rx0, int ry0, int rx1, int ry1) {
    for (float t = 0; t <= 1; t += 0.001) {  
        float h1 = 2 * t * t * t - 3 * t * t + 1;
        float h2 = -2 * t * t * t + 3 * t * t;     
        float h3 = t * t * t - 2 * t * t + t;     
        float h4 = t * t * t - t * t;         

        float xt = h1 * x0 + h2 * x1 + h3 * rx0 + h4 * rx1;
        float yt = h1 * y0 + h2 * y1 + h3 * ry0 + h4 * ry1;

        putpixel(xt, yt, WHITE); 
    }
}

int main() {
    int gd = DETECT, gm;
    initgraph(&gd, &gm, "");

    int x0 = 100, y0 = 400;
    int x1 = 400, y1 = 100;

    int rx0 = 200, ry0 = 0;  
    int rx1 = 200, ry1 = 0; 

    setcolor(RED);
    line(x0, y0, x1, y1);

    drawHermite(x0, y0, x1, y1, rx0, ry0, rx1, ry1);

    getch();
    closegraph();
    return 0;
}
