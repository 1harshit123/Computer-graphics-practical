#include <graphics.h>
#include <iostream>
#include <cmath>
using namespace std;

void translate2D(int &x, int &y, int tx, int ty) {
    x += tx;
    y += ty;
}

void scale2D(int &x, int &y, float sx, float sy, int cx, int cy) {
    x = round(cx + (x - cx) * sx);
    y = round(cy + (y - cy) * sy);
}

void rotatePoint(int &x, int &y, int cx, int cy, int angle) {
    float rad = angle * M_PI / 180;
    int tempX = x, tempY = y;

    x = round(cx + (tempX - cx) * cos(rad) - (tempY - cy) * sin(rad));
    y = round(cy + (tempX - cx) * sin(rad) + (tempY - cy) * cos(rad));
}

int main() {
    int window_width = 1200;
    int window_height = 800;

    initwindow(window_width, window_height, "2D Transformations");

    int x1 = 300, y1 = 200, x2 = 600, y2 = 400;

    setcolor(RED);
    rectangle(x1, y1, x2, y2);
    outtextxy(50, 50, "Original Rectangle");

    // Translation
    int tx = 100, ty = 100;
    int translatedX1 = x1, translatedY1 = y1;
    int translatedX2 = x2, translatedY2 = y2;
    translate2D(translatedX1, translatedY1, tx, ty);
    translate2D(translatedX2, translatedY2, tx, ty);

    setcolor(GREEN);
    rectangle(translatedX1, translatedY1, translatedX2, translatedY2);
    outtextxy(50, 70, "Translated Rectangle");

    // Scaling
    float sx = 1.5, sy = 1.5;
    int centerX = (translatedX1 + translatedX2) / 2;
    int centerY = (translatedY1 + translatedY2) / 2;

    int scaledX1 = translatedX1, scaledY1 = translatedY1;
    int scaledX2 = translatedX2, scaledY2 = translatedY2;
    scale2D(scaledX1, scaledY1, sx, sy, centerX, centerY);
    scale2D(scaledX2, scaledY2, sx, sy, centerX, centerY);

    setcolor(BLUE);
    rectangle(scaledX1, scaledY1, scaledX2, scaledY2);
    outtextxy(50, 90, "Scaled Rectangle");

    // Rotation
    int angle = 45;

    int rx1 = scaledX1, ry1 = scaledY1;
    int rx2 = scaledX2, ry1_rotated = scaledY1;
    int rx3 = scaledX2, ry3 = scaledY2; 
    int rx4 = scaledX1, ry4 = scaledY2; 

    rotatePoint(rx1, ry1, centerX, centerY, angle);
    rotatePoint(rx2, ry1_rotated, centerX, centerY, angle);
    rotatePoint(rx3, ry3, centerX, centerY, angle);
    rotatePoint(rx4, ry4, centerX, centerY, angle);

    setcolor(YELLOW);
    line(rx1, ry1, rx2, ry1_rotated); 
    line(rx2, ry1_rotated, rx3, ry3); 
    line(rx3, ry3, rx4, ry4);         
    line(rx4, ry4, rx1, ry1);         
    outtextxy(50, 110, "Rotated Rectangle");

    getch();
    closegraph();
    return 0;
}
