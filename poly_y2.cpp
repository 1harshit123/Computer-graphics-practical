#include <iostream>
using namespace std;

const int MAX = 100;

struct Point {
    double x, y;
};

struct edge {
    Point b; // Beginning point
    Point e; // Ending point
};

void Output(Point vertex, int *outLength, Point outVertexArray[]) {
    outVertexArray[(*outLength)++] = vertex;
}

bool inside(Point p, edge givenEdge) {
    // Check if point p is inside the edge defined by givenEdge
    double crossProduct = (givenEdge.e.x - givenEdge.b.x) * (p.y - givenEdge.b.y) -
                          (givenEdge.e.y - givenEdge.b.y) * (p.x - givenEdge.b.x);
    return crossProduct <= 0; // Adjust based on your coordinate system
}

Point intersect(Point s, Point p, edge givenEdge) {
    double dx12 = p.x - s.x;
    double dy12 = p.y - s.y;
    double dx34 = givenEdge.e.x - givenEdge.b.x;
    double dy34 = givenEdge.e.y - givenEdge.b.y;

    double denom = dx12 * dy34 - dy12 * dx34;
    
    // Avoid division by zero
    if (denom == 0) return {0, 0}; // or handle as needed

    double t = (dx34 * (s.y - givenEdge.b.y) - dy34 * (s.x - givenEdge.b.x)) / denom;
    
    Point intersection;
    intersection.x = s.x + t * dx12;
    intersection.y = s.y + t * dy12;

    return intersection;
}

void SutherlandHodgmanPolygonClip(Point inVertexArray[], Point outVertexArray[], int inLength, int* outLength, edge frameEdge) {
    Point s = inVertexArray[inLength - 1]; // Start with the last vertex
    *outLength = 0;

    for (int j = 0; j < inLength; j++) {
        Point p = inVertexArray[j];
        if (inside(p, frameEdge)) {
            if (inside(s, frameEdge)) {
                Output(p, outLength, outVertexArray);
            } else {
                Point i = intersect(s, p, frameEdge);
                Output(i, outLength, outVertexArray);
                Output(p, outLength, outVertexArray);
            }
        } else {
            if (inside(s, frameEdge)) {
                Point i = intersect(s, p, frameEdge);
                Output(i, outLength, outVertexArray);
            }
        }
        s = p; // Move to next vertex
    }
}

int main() {
    // Define the polygon vertices
    Point inVertexArray[MAX] = {{150, 400}, {100, 50}, {50, 150}};
    int inLength = 3;

    // Define the clipping edges
    edge frameEdges[4] = {
        {{50, 50}, {350, 50}},   // Bottom edge
        {{350, 50}, {350, 350}}, // Right edge
        {{350, 350}, {50, 350}}, // Top edge
        {{50, 350}, {50, 50}}    // Left edge
    };

    // Array to hold the output vertices
    Point outVertexArray[MAX];
    int outLength;

    // Perform clipping for each edge
    for (int i = 0; i < 4; i++) {
        SutherlandHodgmanPolygonClip(inVertexArray, outVertexArray, inLength, &outLength, frameEdges[i]);
        
        // Copy outVertexArray to inVertexArray for the next iteration
        for (int j = 0; j < outLength; j++) {
            inVertexArray[j] = outVertexArray[j];
        }
        inLength = outLength;
        
        // Reset output length for next iteration
        outLength = 0;
    }

    // Output the clipped polygon vertices
    cout << "Clipped Polygon Vertices: " << endl;
    for (int i = 0; i < inLength; i++) { // Use inLength as it holds final clipped vertices count
        cout << "(" << inVertexArray[i].x << ", " << inVertexArray[i].y << ")" << endl;
    }

    return 0;
}