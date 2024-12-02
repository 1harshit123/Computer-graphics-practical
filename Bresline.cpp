#include <iostream>
#include <graphics.h>
#include <cmath>
using namespace std;

void Bresenhemline(int x0, int y0, int xl, int yl){
    int dx = abs(xl - x0);
    int dy = abs(yl - y0);
    int d = 2 * dy - dx;
    int incE = 2 * dy;
    int incEA = 2 * (dy - dx);
    int x = x0;
    int y = y0;
    line(x * 40, y * 40, x * 40, y * 40);
    while(x < xl){
        if(d <= 0){
            d += incE;
            x++;
            line((x + 1) * 40, (y) * 40, x * 40, y * 40);
        }
        else {
            d += incEA;
            x++;
            y++;
            line((x + 1) * 40, (y + 1) * 40, x * 40, y * 40);
        }
        
    }
}

int main(){
    int x1, y1, x2, y2;
    // cout<<"Enter coordinates of the starting point : ";
    // cin>>x1>>y1;
    // cout<<"Enter coordinates of the ending point : ";
    // cin>>x2>>y2;
    x1=2;
    y1=4;
    x2=7;
    y2=9;
    int gd=DETECT, gm;
    initgraph(&gd, &gm, (char*)"");
    Bresenhemline(x1, y1, x2, y2);

    getch();
    closegraph();

    return 0;
}