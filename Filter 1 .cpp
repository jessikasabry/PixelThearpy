#include<iostream>
#include "Image_Class.h"

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


int main(){

    Image gray_image("Nour.jpg");

    turn_to_gray(gray_image);

    gray_image.saveImage("Nour_gray_filter1.jpg");

    return 0;
}

