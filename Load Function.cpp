 #include<iostream>
#include"Image_Class.h"
using namespace std;
Image image;
string ImageName;
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

