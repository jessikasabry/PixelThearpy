 #include<iostream>
#include"Image_Class.h"
using namespace std;
Image image;
string ImageName;


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

void resize(Image& image, int h,int w){
    int nh,nw;
    cout<<"ENter the new width and the new height of the image;\n";
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
void invertImage(Image& image){
    for (int i = 0; i < image.width; i++) {
        for (int j = 0; j < image.height; j++) {
            for (int c = 0; c < 3; c++) {
                image.getPixel(i, j, c) = 255 - image.getPixel(i, j, c);
            }
        }
    }
}
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

