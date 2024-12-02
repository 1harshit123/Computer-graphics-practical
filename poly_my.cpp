#include <iostream>
using namespace std;
const int MAX = 100;
struct Point 
{
    double x, y;
};
struct edge
{
    Point b;
    Point e;
};


void Output(Point vertex, int *outLength, Point outVertexArray[]) {
    outVertexArray[(*outLength)++] = vertex;
}

bool inside(Point p, edge givenEdge){
    int temp = (givenEdge.e.y - givenEdge.b.y)*(p.y-givenEdge.b.y) + (givenEdge.e.x - givenEdge.b.x)*(p.y-givenEdge.b.y);
    if(temp <= 0){
        return true;
    } else{
        return false;
    }
}

Point intersect(Point s, Point p, edge givenEdge){
    double dx12 = p.x - s.x;
    double dy12 = p.y - s.y;
    double dx34 = givenEdge.e.x - givenEdge.b.x;
    double dy34 = givenEdge.e.y - givenEdge.b.y;

    double denom = dx12 * dy34 - dy12 * dx34;
      double t = (dx34 * (s.y - givenEdge.b.y) - dy34 * (s.x - givenEdge.b.x)) / denom;
    double u = (dx12 * (s.y - givenEdge.b.y) - dy12 * (s.x - givenEdge.b.x)) / denom;

    Point intersection;

    intersection.y = s.y + t * dy12;
    intersection.x = s.x + t * dx12;

    return intersection;
}


void SutherlandHodgmanPolygonClip(Point inVertexArray[], Point outVertexArray[], int inLength, int* outlength, edge frameEdge){
    Point s, p, i;
    int j;
    *outlength = 0;
    s = inVertexArray[inLength - 1];
    for ( j = 0; j < inLength; j++)
    {
        p = inVertexArray[j];
        if (inside(p, frameEdge))
        {
            if (inside(s, frameEdge))
            {
                Output(p, outlength, outVertexArray);
            } else
            {
                i = intersect(s, p, frameEdge);
                Output(i, outlength, outVertexArray);
                Output(p, outlength, outVertexArray);
            }  
        } else
        {
            if (inside(s, frameEdge))
            {
                i = intersect(s, p, frameEdge);
                Output(i, outlength, outVertexArray);
            }
            s = p;
            
        }
        
        
    }
    


}



int main() {
    // Define the polygon vertices
    Point inVertexArray[MAX] = {{150, 400}, {100, 50}, {50, 150}};
    int inLength = 3;

    // Define the clipping edges
    edge frameEdges[4] = {
        {{50, 50}, {350, 50}},   // Bottom edge
        {{50, 350}, {350, 350}}, // Top edge
        {{50, 50}, {50, 350}},   // Left edge
        {{350, 50}, {350, 350}}  // Right edge
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
    }

    // Output the clipped polygon vertices
    cout << "Clipped Polygon Vertices: " << endl;
    for (int i = 0; i < outLength; i++) {
        cout << "(" << outVertexArray[i].x << ", " << outVertexArray[i].y << ")" << endl;
    }

    return 0;
}


