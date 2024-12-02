#include <iostream>
using namespace std;
#include <graphics.h>
#include <cmath>

// Define a small 3D cube with 8 vertices (scaled down)
double vertices[8][3] = {
    {150, 150, 100}, // Front-top-left
    {250, 150, 100}, // Front-top-right
    {250, 250, 100}, // Front-bottom-right
    {150, 250, 100}, // Front-bottom-left
    {150, 150, 200}, // Back-top-left
    {250, 150, 200}, // Back-top-right
    {250, 250, 200}, // Back-bottom-right
    {150, 250, 200}  // Back-bottom-left
};

// Function to draw the 3D figure (projected to 2D)
void drawFigure() {
    // Draw front face (4 vertices)
    for (int i = 0; i < 4; i++) {
        line(vertices[i][0], vertices[i][1], vertices[(i + 1) % 4][0], vertices[(i + 1) % 4][1]);
    }

    // Draw back face (4 vertices)
    for (int i = 4; i < 8; i++) {
        line(vertices[i][0], vertices[i][1], vertices[(i + 1) % 4 + 4][0], vertices[(i + 1) % 4 + 4][1]);
    }

    // Connect front and back faces (8 edges)
    for (int i = 0; i < 4; i++) {
        line(vertices[i][0], vertices[i][1], vertices[i + 4][0], vertices[i + 4][1]);
    }
}

// Apply translation (in 3D)
void translate(double tx, double ty, double tz) {
    for (int i = 0; i < 8; i++) {
        vertices[i][0] += tx;
        vertices[i][1] += ty;
        vertices[i][2] += tz;
    }
}

// Apply rotation around the X-axis
void rotateX(double angle) {
    double rad = angle * M_PI / 180.0;
    double c = cos(rad);
    double s = sin(rad);

    for (int i = 0; i < 8; i++) {
        double y = vertices[i][1];
        double z = vertices[i][2];
        vertices[i][1] = y * c - z * s;
        vertices[i][2] = y * s + z * c;
    }
}

// Apply rotation around the Y-axis
void rotateY(double angle) {
    double rad = angle * M_PI / 180.0;
    double c = cos(rad);
    double s = sin(rad);

    for (int i = 0; i < 8; i++) {
        double x = vertices[i][0];
        double z = vertices[i][2];
        vertices[i][0] = x * c + z * s;
        vertices[i][2] = -x * s + z * c;
    }
}

// Apply rotation around the Z-axis
void rotateZ(double angle) {
    double rad = angle * M_PI / 180.0;
    double c = cos(rad);
    double s = sin(rad);

    for (int i = 0; i < 8; i++) {
        double x = vertices[i][0];
        double y = vertices[i][1];
        vertices[i][0] = x * c - y * s;
        vertices[i][1] = x * s + y * c;
    }
}

// Apply scaling (in 3D)
void scale(double sx, double sy, double sz) {
    for (int i = 0; i < 8; i++) {
        vertices[i][0] *= sx;
        vertices[i][1] *= sy;
        vertices[i][2] *= sz;
    }
}

// Apply reflection in 3D (about x, y, or z axis)
void reflect(int axis) {
    for (int i = 0; i < 8; i++) {
        if (axis == 0) { // Reflect about x-axis
            vertices[i][0] = -vertices[i][0] + 300;
        } else if (axis == 1) { // Reflect about y-axis
            vertices[i][1] = -vertices[i][1] + 300;
        } else if (axis == 2) { // Reflect about z-axis (for simplicity)
            vertices[i][2] = -vertices[i][2] + 300;
        }
    }
}

// Apply shearing (in 3D)
void shear(double shx, double shy, double shz) {
    for (int i = 0; i < 8; i++) {
        double x = vertices[i][0];
        double y = vertices[i][1];
        double z = vertices[i][2];
        vertices[i][0] = x + shx * y + shz * z;
        vertices[i][1] = y + shy * x + shz * z;
        vertices[i][2] = z + shx * x + shy * y;
    }
}

int main() {
    int gd = DETECT, gm;
    initgraph(&gd, &gm, NULL);

    // Draw the original figure
    setcolor(WHITE);
    cout << "ORIGINAL CUBE" << endl;
    drawFigure();
    delay(3000);
    cleardevice();

    // Apply translation
    translate(50, 50, 50); // Translate by 50 units in all 3 directions
    cout << "TRANSLATED CUBE" << endl;
    drawFigure();
    delay(3000);
    cleardevice();

    // Apply rotation around X-axis
    rotateX(45); // Rotate 45 degrees around X-axis
    cout << "ROTATED CUBE (X-axis)" << endl;
    drawFigure();
    delay(3000);
    cleardevice();

    // Apply rotation around Y-axis
    rotateY(45); // Rotate 45 degrees around Y-axis
    cout << "ROTATED CUBE (Y-axis)" << endl;
    drawFigure();
    delay(3000);
    cleardevice();

    // Apply rotation around Z-axis
    rotateZ(45); // Rotate 45 degrees around Z-axis
    cout << "ROTATED CUBE (Z-axis)" << endl;
    drawFigure();
    delay(3000);
    cleardevice();

    // Apply scaling
    scale(0.8, 0.8, 0.8); // Scale down to avoid going out of bounds
    cout << "SCALED CUBE" << endl;
    drawFigure();
    delay(3000);
    cleardevice();

    // Apply reflection
    reflect(0); // Reflect about the X-axis
    cout << "REFLECTED CUBE (X-axis)" << endl;
    drawFigure();
    delay(3000);
    cleardevice();

    // Apply shearing
    shear(0.2, 0.2, 0.2); // Shear with small values to maintain visibility
    cout << "SHEARED CUBE" << endl;
    drawFigure();
    delay(3000);
    cleardevice();

    // Close graphics
    closegraph();
    return 0;
}