#include <iostream>
#include <graphics.h>
using namespace std;

const int INSIDE = 0;
const int LEFT = 1;
const int RIGHT = 2;
const int BOTTOM = 4;
const int TOP = 8;

int x_max, y_max, x_min, y_min;

int computeCode(double x, double y) {
    int code = INSIDE;

    if (x < x_min)
        code = LEFT;
    else if (x > x_max)
        code = RIGHT;

    if (y < y_min)
        code = BOTTOM;
    else if (y > y_max)
        code = TOP;

    return code;
}

void cohenSutherlandClip(double x1, double y1, double x2, double y2) {
    int code1 = computeCode(x1, y1);
    int code2 = computeCode(x2, y2);
    bool accept = false;

    setcolor(RED);
    line(x1, y1, x2, y2);

    while (true) {
        if ((code1 == 0) && (code2 == 0)) {
            accept = true;
            break;
        } else if (code1 & code2) {
            break;
        } else {
            int code_out;
            double x, y;

            if (code1 != 0)
                code_out = code1;
            else
                code_out = code2;

            if (code_out & TOP) {
                x = x1 + (x2 - x1) * (y_max - y1) / (y2 - y1);
                y = y_max;
            } else if (code_out & BOTTOM) {
                x = x1 + (x2 - x1) * (y_min - y1) / (y2 - y1);
                y = y_min;
            } else if (code_out & RIGHT) {
                y = y1 + (y2 - y1) * (x_max - x1) / (x2 - x1);
                x = x_max;
            } else if (code_out & LEFT) {
                y = y1 + (y2 - y1) * (x_min - x1) / (x2 - x1);
                x = x_min;
            }

            if (code_out == code1) {
                x1 = x;
                y1 = y;
                code1 = computeCode(x1, y1);
            } else {
                x2 = x;
                y2 = y;
                code2 = computeCode(x2, y2);
            }
        }
    }

    if (accept) {
        setcolor(GREEN);
        line(x1, y1, x2, y2);
        cout << "Line accepted from (" << x1 << ", " << y1 << ") to (" << x2 << ", " << y2 << ")" << endl;
    } else {
        cout << "Line rejected" << endl;
    }
}

int main() {
    int gd = DETECT, gm;
    initwindow(800, 600);
  
    x_min = 100;
    y_min = 200;
    x_max = 500;
    y_max = 400;

    double x1, y1, x2, y2;
    x1 = 300;
    y1 = 100;
    x2 = 600;
    y2 = 400;

    setcolor(WHITE);
    rectangle(x_min, y_min, x_max, y_max);

    cohenSutherlandClip(x1, y1, x2, y2);

    getch();
    closegraph();
    return 0;
}
