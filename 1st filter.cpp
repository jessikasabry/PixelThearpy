#include<iostream>
#include"Image_Class.h"
using namespace std;
Image image;
 void BlackAndWhite(Image &image){
    for(int y=0;y<image.height;y++){
        for(int x=0;x<image.width;x++){
          int red=image.getPixel(x,y,0);
          int green=image.getPixel(x,y,1);
           int blue=image.getPixel(x,y,2);
           int  gray=(red+green +blue)/3;
           int value;
           if(gray>=127)value=255;
           else value=0;
          image.setPixel(x,y,0,value);
           image.setPixel(x,y,1,value);
            image.setPixel(x,y,2,value);

        }
    }
 }
int main() {
     string ImageName;
     //cout<<"PLEASE ENTER YOUR IMAGE NAME";
     //cin>>ImageName;
     if(image.loadNewImage("paris.jpeg"))
     cout<<"Image successfully uplosded";

     BlackAndWhite(image);
     image.saveImage("BlackAndWhite.jpg");
    cout<<"Image Proceed Successfully";
    return 0;

}