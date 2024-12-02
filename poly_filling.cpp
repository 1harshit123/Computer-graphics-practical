#include <iostream>
#include <graphics.h>
#include <algorithm>
#include <climits>
using namespace std;

const int MAX_VERTICES = 100;

struct Point {
    int x, y;
};

struct Edge {
    int y_max;
    double x_min;
    double slope_inv;
};

void addEdge(Edge edgeTable[][MAX_VERTICES], int edgeCount[], Point p1, Point p2) {
    if (p1.y == p2.y) return;

    if (p1.y > p2.y) swap(p1, p2);

    Edge edge;
    edge.y_max = p2.y;
    edge.x_min = p1.x;
    edge.slope_inv = static_cast<double>(p2.x - p1.x) / (p2.y - p1.y);

    edgeTable[p1.y][edgeCount[p1.y]++] = edge;
}

void scanlineFill(Point polygon[], int n) {
    int y_min = INT_MAX, y_max = INT_MIN;

    for (int i = 0; i < n; i++) {
        y_min = min(y_min, polygon[i].y);
        y_max = max(y_max, polygon[i].y);
    }

    Edge edgeTable[y_max + 1][MAX_VERTICES];
    int edgeCount[y_max + 1] = {0};

    for (int i = 0; i < n; i++) {
        addEdge(edgeTable, edgeCount, polygon[i], polygon[(i + 1) % n]);
    }

    Edge activeEdgeTable[MAX_VERTICES];
    int activeEdgeCount = 0;

    for (int y = y_min; y <= y_max; y++) {
        for (int i = 0; i < edgeCount[y]; i++) {
            activeEdgeTable[activeEdgeCount++] = edgeTable[y][i];
        }

        int newCount = 0;
        for (int i = 0; i < activeEdgeCount; i++) {
            if (activeEdgeTable[i].y_max != y) {
                activeEdgeTable[newCount++] = activeEdgeTable[i];
            }
        }
        activeEdgeCount = newCount;

        sort(activeEdgeTable, activeEdgeTable + activeEdgeCount, [](Edge a, Edge b) {
            return a.x_min < b.x_min;
        });

        for (int i = 0; i < activeEdgeCount; i += 2) {
            if (i + 1 >= activeEdgeCount) break;

            int x_start = static_cast<int>(activeEdgeTable[i].x_min);
            int x_end = static_cast<int>(activeEdgeTable[i + 1].x_min);

            for (int x = x_start; x < x_end; x++) {
                putpixel(x, y, WHITE); // Draw pixel on screen
            }
        }

        for (int i = 0; i < activeEdgeCount; i++) {
            activeEdgeTable[i].x_min += activeEdgeTable[i].slope_inv;
        }
    }
}

int main() {
     int window_width = 1000;
    int window_height = 1000;

    initwindow(window_width, window_height, "Polygon Fill Using Scanline Algorithm");

    int n = 6;
    
Point polygon[MAX_VERTICES] = {
    {500, 200}, // Top
    {350, 400}, // Top-left
    {350, 600}, // Bottom-left
    {650, 600}, // Bottom-right
    {650, 400}, // Top-right
    {500, 200}  // Closing the loop (same as the top)
};

    setcolor(RED);
    for (int i = 0; i < n; i++) {
        line(polygon[i].x, polygon[i].y, polygon[(i + 1) % n].x, polygon[(i + 1) % n].y);
    }

    scanlineFill(polygon, n);

    getch();
    closegraph();
    return 0;
}
