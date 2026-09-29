 #include<iostream>
#include"Image_Class.h"
using namespace std;
Image image;
string ImageName;

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

 void LoadImage(Image &image){
 
    cout<<"Enter Your Image Name";
    cin>>ImageName;
    if(!image.loadNewImage(ImageName))cout<<"Failed Image uploading";
    else cout<<"uploaded Successfully";
    };


    int main(){
        int choice;
        cout<<"Baby Photoshop Program\n";
        cout<<"Choose a option\n";
        cout<<"1.Load Image\n";
        cout<<"2.Choose Filter\n";
        cout<<"3.Save Image\n";
        cout<<"4.exist\n";
        cout<<"choose a Choice\n";
      
        do{
              cin>>choice;
            if(choice==1) LoadImage(image);
            else if(choice==2){//put the menu;
                }
            else if(choice==3){
                image.saveImage("Updated "+ ImageName);
                cout<<"Image  Saved Successfully\n";
            }
            else if(choice==4){
                cout<<"Goodbye!\n";
            }
            else {
                cout<<"Invalid Choice\n";
            }
}while (choice!=4);
return 0;
    }

