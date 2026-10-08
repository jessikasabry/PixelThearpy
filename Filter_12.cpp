#include <iostream>
#include "Image_Class.h"
#include <vector>
#include <cmath>
using namespace std;

void blur(Image& image,int h,int w){
    Image newImage(w,h);
    int r;
    cout<<"Enter blur strength level\n"<<"Light (1 -> 7)\n"<<"Medium(8 -> 15)\n"<<"Heavy(16 -> 20)\n";
    cin>> r;
    vector<vector<vector<int>>> pref(w,vector<vector<int>>(h,vector<int>(3,0)));
    for(int i=0;i<w;i++){
        for(int j=0;j<h;j++){
            for(int k=0;k<3;k++){
                int left = (i>0)? pref[i-1][j][k]:0;
                int up=(j>0)?pref[i][j-1][k]:0;
                int Corner=(i>0 && j>0)? pref[i-1][j-1][k]:0;
                pref[i][j][k]=image(i,j,k)+up+left-Corner;
            }
        }
    }
for(int i=0;i<w;i++){
        for(int j=0;j<h;j++){
            
               int x1= max(0,i-r);
               int x2= min(w-1,i+r);
               int y1= max(0,j-r);
               int y2= min(h-1,j+r);

             for(int k=0;k<3;k++){

                int top = (y1>0)? pref[x2][y1-1][k]:0;
                int Left=(x1>0)?pref[x1-1][y2][k]:0;
                int corner =(x1>0 && y1>0)? pref[x1-1][y1-1][k]:0;

               int sum= pref[x2][y2][k]-top -Left+corner;
               int count = (x2-x1+1)*(y2-y1+1);
               float color=(float)sum/count;
               newImage(i,j,k)=color;

            }
        }
    }
    image = newImage;
}

int main(){
    string fileName;
    cout << "Enter the filename of the image to load: ";
    cin >> fileName;

    Image image(fileName);
   int h= image.height;
   int w= image.width;

    blur(image,h,w);
    //

    cout << "Pls enter image name to store new image\n";
    cout << "and specify extension .jpg, .bmp, .png, .tga:\n ";

    cin >> fileName;
    image.saveImage(fileName);
    return 0;
}
