#include<iostream>
#include"Image_Class.h"
using namespace std;
Image image;
void rotate(Image &image,int angle){
    int OldWidth=image.width;
    int OldHeight=image.height;
     Image rotated;
    if (angle==90){
     rotated=Image(OldHeight,OldWidth);
     for(int y=0;y<OldHeight;y++){
        for(int x=0;x<OldWidth;x++){
            for(int c=0;c<3;c++){
                int newX=OldHeight-1-y;
                int newY=x;
                rotated.setPixel(newX,newY,c,image.getPixel(x,y,c));
            }
        }

     }
    }
    if (angle==180){
     rotated=Image(OldWidth,OldHeight);
     for(int y=0;y<OldHeight;y++){
        for(int x=0;x<OldWidth;x++){
            for(int c=0;c<3;c++){
                int newX=OldWidth-1-x;
                int newY=OldHeight-1-y;
                rotated.setPixel(newX,newY,c,image.getPixel(x,y,c));
            }
        }

     }
    }
    if (angle==270){
     rotated=Image(OldHeight,OldWidth);
     for(int y=0;y<OldHeight;y++){
        for(int x=0;x<OldWidth;x++){
            for(int c=0;c<3;c++){
                int newX=y;
                int newY=OldWidth-1-x;
                rotated.setPixel(newX,newY,c,image.getPixel(x,y,c));
            }
        }
     }
    }
    image=rotated;
};

int main(){
    string imagename;
    //cout<<"Enter Your Image Name";
   // cin>>imagename;
    if(!image.loadNewImage("night3.jpg")){
        cout<<"uploaded Successfully";
    }
    cout<<"Choose Rotation Angle:\n";
    cout<<"A.rotate 90 degrees\n";
    cout<<"B.rotate 180 degrees\n";
    cout<<"C.rotate 270 degrees\n";
    cout<<"Choose a Letter";
    char angle;
    cin>>angle;
    switch (angle){
        case 'A':
        rotate(image,90);
        break;
        case 'B':
        rotate(image,180);
        break;
        case 'C':
        rotate(image,270);
        break;
       default:
       cout<<"Invalid Choice";return 0;
    }
    image.saveImage("Rotated.jpeg");
    cout<<"Updated Successfully";

    return 0;

}