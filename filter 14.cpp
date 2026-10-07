#include<iostream>
#include"Image_Class.h"
using namespace std;
Image image;

void  OldTV(Image &image){
    int width=image.width;
    int height=image.height;
    for(int y=0;y<image.height;y++){
        if(y%4==0){
        for(int x=0;x<image.width;x++){
          int red=image.getPixel(x,y,0);
          int green=image.getPixel(x,y,1);
           int blue=image.getPixel(x,y,2);
           red=red*0.5;
           green =green*0.5;
           blue=blue*0.5;
            image.setPixel(x,y,0,red);
           image.setPixel(x,y,1,green);
           image.setPixel(x,y,2,blue);


        }
     }
    }
}
int main() {
     string ImageName,UpdatedImage;
     cout<<"PLEASE ENTER YOUR IMAGE NAME";
     cin>>ImageName;
     if(!image.loadNewImage(ImageName)){
        cout<<"Failed to uploade";
    return 0;
}
     cout<<"Image successfully uploded";

    OldTV(image);
    cout<<"Please Enter the name you want for the updated image";
    cin>>UpdatedImage;
     image.saveImage(UpdatedImage);
    cout<<"Image Proceed Successfully";
    return 0;

}
