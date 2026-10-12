# pragma once


#include<iostream>
#include "Image_Class.h"
# include <cmath>
#include <vector>
#include<algorithm>

using namespace std;

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

void applyframe(Image& image, int frameSize,int choice){

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


//salma Darken-Lighten filter 7

void Darken_Lighten(Image& image, int level,int choice) {



    for (int i = 0; i < image.width; i++) {
        for (int j = 0; j < image.height; j++) {
            for (int c = 0; c < 3; c++) {
                int p = image.getPixel(i, j, c);
                int newValue;

                if (choice == 1) {
                    newValue = p * (1.0 - (level / 100.0));

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

                image.setPixel(i, j, c, newValue);
            }
        }
    }
}



// Jana resize filter 8
void resize(Image& image, int nw,int nh){

    float scaleH=(float)image.height/nh;
    float scaleW=(float)image.width/nw;

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



void Samurai(Image & image){
    int w = image.width;
    int h=image.height;

    for(int i=0;i<w;i++){
        for(int j=0;j<h;j++){
            int avg=(  image(i,j,0)+  image(i,j,1)+  image(i,j,2))/3;


            image(i,j,0)=255;

            image(i,j,1)=255-avg;
            image(i,j,2)=255-avg;


        }
    }

}



void blur(Image& image,int r){

    int w = image.width;
    int h=image.height;
    Image newImage(w,h);

    vector<vector<vector<int>>> pref(w,vector<vector<int>>(h,vector<int>(3,0)));
    for(int i=0;i<w;i++){
        for(int j=0;j<h;j++){
            for(int k=0;k<3;k++){
                int left = (i>0)? pref[i-1][j][k]:0;
                int up=(j>0)?pref[i][j-1][k]:0;
                int Corner=(i>0 && j>0)? pref[i-1][j-1][k]:0;
                pref[i][j][k]=image(i,j,k)+up+left-Corner;
            }
        }
    }
    for(int i=0;i<w;i++){
        for(int j=0;j<h;j++){

            int x1= max(0,i-r);
            int x2= min(w-1,i+r);
            int y1= max(0,j-r);
            int y2= min(h-1,j+r);

            for(int k=0;k<3;k++){

                int top = (y1>0)? pref[x2][y1-1][k]:0;
                int Left=(x1>0)?pref[x1-1][y2][k]:0;
                int corner =(x1>0 && y1>0)? pref[x1-1][y1-1][k]:0;

                int sum= pref[x2][y2][k]-top -Left+corner;
                int count = (x2-x1+1)*(y2-y1+1);
                float color=(float)sum/count;
                newImage(i,j,k)=color;

            }
        }
    }
    image = newImage;
}






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








void image_resizing (Image &image , int new_width, int new_height){

    Image new_image (new_width, new_height);

    for (int new_x=0; new_x < new_image.width ; ++new_x){

        for (int new_y=0; new_y < new_image.height ; ++new_y){

            int old_x= new_x * image.width/new_image.width;

            int old_y= new_y * image.height/new_image.height;


            for(int color=0 ; color<3; ++color){

                new_image(new_x,new_y,color)=image(old_x,old_y, color);

            }

        }

    }

    image=new_image;
}



void merge_images(Image &image1, Image &image2, int choice){

    int width;
    int  height;
    if (image1.width==image2.width && image1.height==image2.height){

        width=image1.width; height=image1.height;
    }

    else{



        if(choice==1){

            if(image1.width>image2.width){

                width=image1.width;

            }

            else{ width =image2.width;}

            if(image1.height>image2.height){

                height=image1.height;

            }

            else{height=image2.height;}

            image_resizing(image1,width,height);
            image_resizing(image2,width,height);



        }

        else if  (choice==2){

            if(image1.width<image2.width){

                width=image1.width;

            }

            else{ width =image2.width;}

            if(image1.height<image2.height){

                height=image1.height;

            }
            else{height=image2.height;}


        }

        else{

            return;
        }



    }


    Image merged_photo(width,height);
    for (int x =0 ; x < width;++x){

        for (int y=0; y< height; ++y){

            for(int color=0; color <3; ++color){

                merged_photo(x,y,color)=(image1(x,y,color)+image2(x,y,color))/2;


            }
        }
    }

    image1=merged_photo;
}






void increase_brightness(Image &image){
    for (int row=0 ;row < image.height; ++row ){

        for( int col=0 ; col< image.width;++col){

            int red= image.getPixel(col,row,0);
            int green = image.getPixel(col,row,1);
            int blue = image.getPixel(col,row,2);


            red+=70; green+=50;

            if(red>255){red=255;}
            if(green>255){green=255;}
            if(blue>255){blue=255;}


            image.setPixel(col,row,0,red);
            image.setPixel(col,row,1,green);


        }
    }

}



Image cropImage(Image& image, int X, int Y, int W, int H) {
    Image croppedImage(W, H);
    for(int newY = 0; newY < H; newY++) {
        for(int newX = 0; newX < W; newX++) {
            int originalX = X + newX;
            int originalY = Y + newY;

            for(int c = 0; c < 3; c++) {
                int value = image.getPixel(originalX, originalY, c);
                croppedImage.setPixel(newX, newY, c, value);
            }
        }
    }

    return croppedImage;
}



void oilPainting(Image& image) {
    Image result(image.width, image.height);

    const int levels = 16;
    const int radius = 3;

    for (int i = 0; i < image.height; i++) {
        for (int j = 0; j < image.width; j++) {
            int count[levels] = { 0 };

            for (int y = i - radius; y <= i + radius; y++) {
                for (int x = j - radius; x <= j + radius; x++) {
                    if ( x >= 0 && x < image.width && y >= 0 && y < image.height) {

                        int red = image.getPixel(x, y, 0);
                        int green = image.getPixel(x, y, 1);
                        int blue = image.getPixel(x, y, 2);

                        int intensity = (red + green + blue) / 3;

                        int level = intensity * levels / 256;

                        count[level]++;
                    }
                }
            }

            int dominantLevel = 0;

            for (int k = 1; k < levels; k++) {
                if (count[k] > count[dominantLevel]) {
                    dominantLevel = k;
                }
            }

            int redSum = 0;
            int greenSum = 0;
            int blueSum = 0;

            int pixelCount = 0;

            for (int y = i - radius; y <= i + radius; y++) {
                for (int x = j - radius; x <= j + radius; x++) {
                    if ( x >= 0 && x < image.width && y >= 0 && y < image.height) {

                        int red = image.getPixel(x, y, 0);
                        int green = image.getPixel(x, y, 1);
                        int blue = image.getPixel(x, y, 2);

                        int intensity = (red + green + blue) / 3;

                        int level = intensity * levels / 256;

                        if (level == dominantLevel) {
                            redSum += red;
                            greenSum += green;
                            blueSum += blue;

                            pixelCount++;
                        }
                    }

                }
            }

            if (pixelCount > 0) {
                int newRed = redSum / pixelCount;
                int newGreen = greenSum / pixelCount;
                int newBlue = blueSum / pixelCount;

                if(newRed > 255)newRed = 255;
                if(newGreen > 255)newGreen = 255;
                if(newBlue > 255)newBlue = 255;

                if(newRed < 0)newRed = 0;
                if(newGreen < 0)newGreen = 0;
                if(newBlue < 0)newBlue = 0;

                result.setPixel(j, i, 0, newRed);
                result.setPixel(j, i, 1, newGreen);
                result.setPixel(j, i, 2, newBlue);


            }
        }
    }

    image = result;
}





void purpleEffect(Image& image) {
    for (int i = 0; i < image.height; i++) {
        for(int j = 0; j < image.width; j++) {
            int red = image.getPixel(j, i, 0);
            int green = image.getPixel(j, i, 1);
            int blue = image.getPixel(j, i, 2);

            int newRed = red + 0.4 * blue;
            int newGreen = green * 0.6;
            int newBlue = blue + 0.15 * red;

            if (newRed > 255) newRed = 255;
            if (newGreen > 255) newGreen = 255;
            if (newBlue > 255) newBlue = 255;

            newRed = newRed * 0.78;
            newGreen = newGreen * 0.78;
            newBlue = newBlue * 0.78;

            int average = (newRed + newGreen + newBlue) /3;

            newRed = average + (newRed - average) * 1.20;
            newGreen = average + (newGreen - average) * 1.20;
            newBlue = average + (newBlue - average) * 1.20;

            if (newRed > 255) newRed = 255;
            if (newGreen > 255) newGreen = 255;
            if (newBlue > 255) newBlue = 255;

            if (newRed < 0) newRed = 0;
            if (newGreen < 0) newGreen = 0;
            if (newBlue < 0) newBlue = 0;

            image.setPixel(j, i, 0, newRed);
            image.setPixel(j, i, 1, newGreen);
            image.setPixel(j, i, 2, newBlue);
        }
    }
}













