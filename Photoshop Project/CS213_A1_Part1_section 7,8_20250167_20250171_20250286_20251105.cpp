/* 

CS213 Object Oriented Programming
Assignment 1 - Part 1

Section: s7 ,S8

Team Members:
1. Joussyana  ID: 20250167
2. Jessika - ID: 20250171
3. Salma - ID: 20250286
4. Jana - ID: 20251105

Work Breakdown:
Joussyana: Filters 1, 5
Jessika: Filters 2, 6
Salma: Filters 3, 7
Jana: Filters 4, 8

Menu , load and save : team work

*/

#include<iostream>
#include<cmath>
#include "Image_Class.h"
using namespace std;
Image image;
string ImageName;

// joussyana image to gray filter 1
void turn_to_gray(Image &image ) {
    for(int i=0;i < image.width;++i){
        for(int j=0;j< image.height;++j){
        
            unsigned int average =0 ;

            for (int k=0 ; k< 3 ;++k ){
                average +=image(i,j,k);
            }
            average/=3;
             for (int k=0 ; k< 3 ;++k ){
                image(i,j,k)=average;
            }
    }
   
    }
}

// jessika _filter 2
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
 
 // Salma invert filter 3 
void invertImage(Image& image){
    for (int i = 0; i < image.width; i++) {
        for (int j = 0; j < image.height; j++) {
            for (int c = 0; c < 3; c++) {
                image.getPixel(i, j, c) = 255 - image.getPixel(i, j, c);
            }
        }
    }
}

// jana frame filter 4

void applyframe(Image& image, int frameSize){
    cout<< "Choose frame style:\n"<<"1.simple frame"<<endl<<"2.Fancy frame"<<endl;
    int choice;
    cin>>choice;
    if(choice==1){
 for(int i=0;i<image.width;i++){
    for(int j=0;j<image.height;j++){
        for(int k=0;k<3;k++){
            if(i<frameSize || i>=image.width-frameSize || j<frameSize || j>=image.height-frameSize){
                image(i,j,0)=0;
                image(i,j,1)=0;
                image(i,j,2)=0;
            }
        }
    }
 }
    }
    else if(choice==2){
        for(int i=0;i<image.width;i++){
            for(int j=0;j<image.height;j++){
                for(int k=0;k<3;k++){
                    if(i<frameSize+5 || i>=image.width-(frameSize+5) || j<frameSize+5 || j>=image.height-(frameSize+5)){
                        image(i,j,k)=255;
                        
                    }
                 if(i<frameSize || i>=image.width-frameSize || j<frameSize || j>=image.height-frameSize){
                image(i,j,0)=0;
                image(i,j,1)=0;
                image(i,j,2)=0;
            }
                 if(i<5 || i>=image.width-(5) || j<5 || j>=image.height-(5)){
                        image(i,j,k)=255;
                        
                    }
                }
            }
        }
    }

}

// joussyana  flipping filter 5 

void flip_right_to_left (Image &photo) {
    for(int j=0; j< photo.height; ++j){

        int left=0, right= (photo.width)-1;

        while(left<right){
             for(int k=0; k<3; k++){

                unsigned temp=photo(left ,j,k );

                photo(left,j,k)=photo(right,j,k);

                photo(right,j,k)=temp;

             }

             ++left; --right;
        }
    }
}



void flip_top_to_bottom (Image &photo) {
    for(int i=0; i< photo.width; ++i){

        int top=0, bottom= (photo.height)-1;

        while(top<bottom){
             for(int k=0; k<3; k++){

                unsigned temp=photo(i ,top,k );

                photo(i,top,k)=photo(i,bottom,k);

                photo(i,bottom,k)=temp;

             }

             ++top; --bottom;
        }
    }
}


void flip (Image &image ){
    int choice;
    cout<< " choose flip direction: \n";
    cout <<"1. flip right to left \n";
    cout<<" 2. flip top to bottom \n";
    cout<<"Enter your choice " ;
    cin>> choice ;

    if (choice==1){
        flip_right_to_left(image);
        cout<<"image flipped Right to Left successfully!\n";

    }
     
    else if (choice==2){
        flip_top_to_bottom (image);
         cout<<"image flipped Top to Bottom successfully!\n";
    }
    else
    {
        cout<<" Invalid choice! \n ";
    }
}

// Jessika Rotation filter 6 
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
}

void Rotate (Image &image ){
    int choice ;
    cout<< "\nChoose rotation angle:\n";
    cout<<"1.Rotate 90 degrees \n";
    cout<<"2.Rotate 180 degrees \n";
    cout<<"3.Rotate 270 degrees \n";
    cout<<"Enter your choice: ";
    cin>> choice;

    if(choice==1){
        rotate (image,90);
    }
    else if(choice==2){
        rotate (image,180);
    }
    else  if(choice==3){
        rotate (image,270);
    }

    else{

        cout<<"invalid choice!\n";
    }
}
//salma lighthing filter 7

void Darken_Lighten(Image& image, int level) {
    int choice;

    cout << "Do you want to: \n";
    cout << "1. Darken image\n";
    cout << "2. Lighten image\n";
    cin >> choice;

    while (choice != 1 && choice != 2) {
        cout << "Invalid choice. Please enter 1 for Darken or 2 for Lighten: ";
        cin >> choice;
    }

    for (int i = 0; i < image.width; i++) {
        for (int j = 0; j < image.height; j++) {
            for (int c = 0; c < 3; c++) {
                int p = image.getPixel(i, j, c);
                int newValue;

                if (choice == 1) {
                     double t = level / 100.0;
                     double factor = pow(0.05, t);
                     newValue = p * factor;

                     if (newValue < 0) {
                        newValue = 0;
                     }
                }

                else if (choice == 2) {
                    newValue = p * (1 + level / 100.0);

                    if (newValue > 255) {
                        newValue = 255;
                    }
                }

                image.getPixel(i, j, c) = newValue;
            }
        }
    }
}



// Jana resize filter 8
void resize(Image& image, int h,int w){
    int nh,nw;
    cout<<"Enter the new width and the new height of the image;\n";
    cin>>nw>>nh;
    float scaleH=(float)h/nh;
    float scaleW=(float)w/nw;

    Image newImage(nw,nh);

    for(int i=0;i<nw;i++){
        for(int j=0;j<nh;j++){
            for(int k=0;k<3;k++){
                int oldX=(int)(i*scaleW);
                int oldY=(int)(j*scaleH);
                newImage(i,j,k)=image(oldX,oldY,k);

            }

        }

    }
image=newImage;


}




 // Load image 

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
cout<<"1.LoadImage\n";
cout<<"2.Choose Filter\n";
cout<<"3.Save Image\n";
cout<<"4.exist\n";
 cout<<"choose a Choice\n";
      
 do{
    cin>>choice;
    if(choice==1) LoadImage(image);
    else if(choice==2){int filterChoice;

    cout<<"\nchoose a filter \n";
    cout<<"1.GrayScale\n";
    cout<<"2.BlackAndWhite\n";
    cout<<"3.Invert\n";
    cout<<"4.Frame\n";
    cout<<"5.Flip\n";
    cout<<"6.Rotate\n";
    cout<<"7.DarKen/Lighten\n";
   cout<<"8.Resize";
   cout<<"Choose a filter :" ;

cin>> filterChoice;

if(filterChoice == 1){
     turn_to_gray(image);
     cout<< "GrayScale Filter Applied Successfully! \n";
}

else if(filterChoice == 2){
     BlackAndWhite(image);
     cout<< "Black & white  Filter Applied Successfully !\n";
}
else if(filterChoice == 3){
     invertImage (image);
     cout<< "Invert Filter Applied Successfully !\n";
}
else if(filterChoice == 4){
     applyframe (image ,10);
     cout<< "Frame Filter Applied Successfully !\n";
}
else if(filterChoice == 5){
    flip(image ) ;
     
}
 else if(filterChoice == 6){
    Rotate (image ) ;
     
}
else if(filterChoice == 7){
   int level;
   cout<<"Enter the level (0-100): " ;
   cin >> level;

   while (level< 0|| level >100){
    cout <<"Invalid level . Enter a value between 0 and 100 : ";
    cin>> level;
   }
    Darken_Lighten(image , level);
}
else if(filterChoice == 8){
    resize (image ,image.height , image.width);
     cout<< "Resize Filter Applied Successfully !\n";
}

else{

    cout<<" Invalid Filter Choice \n";
}

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

