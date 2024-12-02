#include <iostream>
#include <iomanip>  // for setprecision
using namespace std;

const int MAX = 100; // Maximum number of vertices in the polygon

struct Point {
    int x, y;
};

// Function to output a point to the clipped polygon
void Output(Point vertex, int *outLength, Point outVertexArray[]) {
    outVertexArray[(*outLength)++] = vertex;
}

// Function to check if a vertex is inside a specific edge
bool Inside(Point p, Point edgeStart, Point edgeEnd) {
    return (edgeEnd.x - edgeStart.x) * (p.y - edgeStart.y) - (edgeEnd.y - edgeStart.y) * (p.x - edgeStart.x) >= 0;
}

// Function to find the intersection point of a line segment with the edge
Point Intersect(Point s, Point p, Point edgeStart, Point edgeEnd) {
    double dx1 = p.x - s.x, dy1 = p.y - s.y;
    double dx2 = edgeEnd.x - edgeStart.x, dy2 = edgeEnd.y - edgeStart.y;
    double denominator = dx1 * dy2 - dy1 * dx2;

    Point intersect;
    if (denominator == 0) { // Parallel lines; return s as a fallback
        intersect = s;
    } else {
        double t = ((s.x - edgeStart.x) * dy2 - (s.y - edgeStart.y) * dx2) / denominator;
        intersect.x = static_cast<int>(s.x + t * dx1 + 0.5); // Round to nearest integer
        intersect.y = static_cast<int>(s.y + t * dy1 + 0.5); // Round to nearest integer
    }

    // Debug output for intersection point
    cout << "Intersect between (" << s.x << ", " << s.y << ") and (" << p.x << ", " << p.y 
         << ") with edge (" << edgeStart.x << ", " << edgeStart.y << ") -> (" << edgeEnd.x 
         << ", " << edgeEnd.y << ") at (" << intersect.x << ", " << intersect.y << ")\n";

    return intersect;
}

// Sutherland-Hodgman Polygon Clipping Algorithm for a single edge
void ClipEdge(Point inVertexArray[], Point outVertexArray[], int inLength, int *outLength, Point edgeStart, Point edgeEnd) {
    Point s, p, i;
    *outLength = 0;
    s = inVertexArray[inLength - 1]; // Start with the last vertex as the starting vertex

    for (int j = 0; j < inLength; j++) {
        p = inVertexArray[j];
        if (Inside(p, edgeStart, edgeEnd)) {
            if (!Inside(s, edgeStart, edgeEnd)) {
                i = Intersect(s, p, edgeStart, edgeEnd);
                Output(i, outLength, outVertexArray);
            }
            Output(p, outLength, outVertexArray);
        } else if (Inside(s, edgeStart, edgeEnd)) {
            i = Intersect(s, p, edgeStart, edgeEnd);
            Output(i, outLength, outVertexArray);
        }
        s = p;
    }
}

// Function to clip against all four edges of a rectangular frame
void SutherlandHodgmanPolygonClip(Point inVertexArray[], int inLength, Point frame[]) {
    Point tempArray1[MAX], tempArray2[MAX];
    int tempLength1 = inLength, tempLength2;

    // Copy the input vertices to a temporary array
    for (int i = 0; i < inLength; i++) {
        tempArray1[i] = inVertexArray[i];
    }

    // Clip against each of the four edges of the rectangular frame
    for (int i = 0; i < 4; i++) {
        Point edgeStart = frame[i];
        Point edgeEnd = frame[(i + 1) % 4]; // Wrap around to the first point for the last edge
        ClipEdge(tempArray1, tempArray2, tempLength1, &tempLength2, edgeStart, edgeEnd);

        // Debug output to track each stage of the clipping
        cout << "After clipping against edge (" << edgeStart.x << ", " << edgeStart.y 
             << ") -> (" << edgeEnd.x << ", " << edgeEnd.y << "): ";
        for (int k = 0; k < tempLength2; k++) {
            cout << "(" << tempArray2[k].x << ", " << tempArray2[k].y << ") ";
        }
        cout << endl;

        // Swap arrays and lengths for the next edge
        tempLength1 = tempLength2;
        for (int j = 0; j < tempLength1; j++) {
            tempArray1[j] = tempArray2[j];
        }
    }

    // Output the final clipped polygon vertices
    cout << "Clipped Polygon Vertices: ";
    for (int i = 0; i < tempLength1; i++) {
        cout << "(" << tempArray1[i].x << ", " << tempArray1[i].y << ") ";
    }
    cout << endl;
}

// Main function to test the algorithm
int main() {
    Point inVertexArray[MAX] = {{1, 1}, {5, 1}, {5, 4}, {1, 4}}; // Input polygon vertices
    int inLength = 4; // Number of vertices in the input polygon

    // Define the rectangular frame by its four corners (counterclockwise order)
    Point frame[4] = {{2, 2}, {10, 2}, {10, 6}, {2, 6}};

    // Perform clipping against the frame
    SutherlandHodgmanPolygonClip(inVertexArray, inLength, frame);

    return 0;
}
