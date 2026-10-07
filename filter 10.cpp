#include<iostream>
#include"Image_Class.h"
#include<cstdlib>
using namespace std;
Image image;

void  DetectedEdge(Image &image){
    int width=image.width;
    int height=image.height;
    for(int y=0;y<image.height;y++){
        for(int x=0;x<image.width;x++){
          int red=image.getPixel(x,y,0);
          int green=image.getPixel(x,y,1);
           int blue=image.getPixel(x,y,2);
           int  gray=(red+green +blue)/3;
           image.setPixel(x,y,0,gray);
           image.setPixel(x,y,1,gray);
           image.setPixel(x,y,2,gray);

        }
    }
        Image result(width,height);
        int thershold=26;
        for(int y=0;y<height;y++){
            for(int x=0;x<width;x++){
                int current=image.getPixel(x,y,0);
                bool edge=false;
                if(x< width-1){
                    int right=image.getPixel(x+1,y,0);
                    if(abs(current-right)>thershold){
                        edge=true;
                    };
                }
                if(y< height-1){
                    int below=image.getPixel(x,y+1,0);
                    if(abs(current-below)>thershold){
                        edge=true;
                    }  
                }
                if (edge){
                  result.setPixel(x,y,0,0);
                  result.setPixel(x,y,1,0);
                  result.setPixel(x,y,2,0);
                }
                else{
                result.setPixel(x,y,0,255);
                result.setPixel(x,y,1,255);
                result.setPixel(x,y,2,255);
            }}

        }
 
 image=result;
}



int main() {
     string ImageName,UpdatedImage;
     cout<<"PLEASE ENTER YOUR IMAGE NAME";
     cin>>ImageName;
     if(image.loadNewImage(ImageName))
     cout<<"Image successfully uploded";

    DetectedEdge(image);
    cout<<"Please Enter the name you want for the updated image";
    cin>>UpdatedImage;
     image.saveImage(UpdatedImage);
    cout<<"Image Proceed Successfully";
    return 0;

}
