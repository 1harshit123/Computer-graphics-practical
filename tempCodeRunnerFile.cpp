#include<iostream>
#include<graphics.h>
#include<cmath>
using namespace std;

void DDA(int x1, int y1, int x2, int y2) {
    // Calculate dx and dy
    int dx = x2 - x1;
    int dy = y2 - y1;

    // Calculate the number of steps
    int steps = abs(dx) > abs(dy) ? abs(dx) : abs(dy);

    // Calculate the increment in x and y for each step
    float xIncrement = dx / (float) steps;
    float yIncrement = dy / (float) steps;

    // Start from the initial point
    float x = x1;
    float y = y1;

    // Plot the points
    for (int i = 0; i <= steps; i++) {
        putpixel(round(x), round(y), WHITE); // Plot pixel
        x += xIncrement; // Increment x
        y += yIncrement; // Increment y
    }
}

int main() {
    // Initialize graphics window
    int gd = DETECT, gm;
    initgraph(&gd, &gm, (char*)"");

    // Input the starting and ending coordinates
    int x1 = 100, y1 = 100, x2 = 400, y2 = 300;

    // Call DDA function to draw line
    DDA(x1, y1, x2, y2);

    // Wait for a key press and close the graphics window
    getch();
    closegraph();

    return 0;
}