#include <iostream> 
#include "Image_Class.h"
using namespace std;


void Samurai(Image & image,int h,int w){

for(int i=0;i<w;i++){
    for(int j=0;j<h;j++){
        int avg=(  image(i,j,0)+  image(i,j,1)+  image(i,j,2))/3;
        

            image(i,j,0)=255;
            
            image(i,j,1)=255-avg;
            image(i,j,2)=255-avg;

        
    }
}

}

int main(){
    string fileName;
    cout << "Enter the filename of the image to load: "<<endl;
    cin >> fileName;

    Image image(fileName);
   int h=image.height;
   int w=image.width;

    Samurai(image,h,w);

    cout << "Pls enter image name to store new image\n ";
    cout << "and specify extension .jpg, .bmp, .png, .tga:\n ";

    cin >> fileName;
    image.saveImage(fileName);
    return 0;
}
