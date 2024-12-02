#include <graphics.h>
#include <iostream>
#include <cmath>
using namespace std;

void drawBezier(int x[], int y[]) {
    for (float t = 0; t <= 1; t += 0.001) { 
        float xt = pow(1 - t, 3) * x[0] +
                   3 * t * pow(1 - t, 2) * x[1] +
                   3 * pow(t, 2) * (1 - t) * x[2] +
                   pow(t, 3) * x[3];

        float yt = pow(1 - t, 3) * y[0] +
                   3 * t * pow(1 - t, 2) * y[1] +
                   3 * pow(t, 2) * (1 - t) * y[2] +
                   pow(t, 3) * y[3];

        putpixel(xt, yt, WHITE);
    }
}

int main() {
    int gd = DETECT, gm;
    initgraph(&gd, &gm, "");

    int x[] = {200, 100, 300, 400} ; 
    int y[] = {500, 100, 300, 200};

    setcolor(RED);
    for (int i = 0; i < 3; i++) {
        line(x[i], y[i], x[i + 1], y[i + 1]); 
    }

    drawBezier(x, y);

    getch();
    closegraph();
    return 0;
}
