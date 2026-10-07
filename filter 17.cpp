#include<iostream>
#include"Image_Class.h"
#include<cmath>
using namespace std;
Image image;
void skweness(Image &image,int angle){
    int width=image.width;
    int height=image.height;
     
      double rad=(angle*3.14285714)/180.0;
    double shear=tan(rad);
    double centerY=(height-1)/2.0;
    double topShift=-(0-centerY)*shear;
    double bottomShift=-((height-1)-centerY)*shear;
    double minShift=min(topShift,bottomShift);
    double maxShift=max(topShift,bottomShift);

int newWidth=width+(int)ceil(maxShift-minShift);

    Image skweed(newWidth,height);
     for(int y=0;y<height;y++){
        for(int x=0;x<newWidth;x++){
           skweed.setPixel(x,y,0,255);
           skweed.setPixel(x,y,1,255);
           skweed.setPixel(x,y,2,255);

        }
    }
   
    for(int y=0;y<height;y++){
        double shift=-(y-centerY)*shear;
        for(int x=0;x<width;x++){
         int newX = (int) round(x+shift-minShift);

        if(newX>=0 && newX<newWidth){
        int red=image.getPixel(x,y,0);
          int green=image.getPixel(x,y,1);
           int blue=image.getPixel(x,y,2);

           skweed.setPixel(newX,y,0,red);
           skweed.setPixel(newX,y,1,green);
           skweed.setPixel(newX,y,2,blue);
            }

        }
    }
    image=skweed;

}
int main() {
     string ImageName,UpdatedImage;
     cout<<"PLEASE ENTER YOUR IMAGE NAME";
     cin>>ImageName;
     if(!image.loadNewImage(ImageName)){
        cout<<"Failed to upload";
    return 0;
}
     cout<<"Image successfully uploded";
     int angle;
    cout<<"Please Enter The Angle of Skweeness you want";
    cin>>angle;

    skweness(image,angle);
    cout<<"Please Enter the name you want for the updated image";
    cin>>UpdatedImage;
     image.saveImage(UpdatedImage);
    cout<<"Image Proceed Successfully";
    return 0;
}
