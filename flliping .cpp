
//filter 5

#include<iostream>
#include "Image_Class.h"


//fllipping left to right

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




int main(){
     Image my_photo("mario.jpg");
     Image left_right(my_photo);
     Image up_down(my_photo);
     flip_right_to_left (left_right);
      flip_top_to_bottom (up_down);
     left_right.saveImage("flip_right_to_left mario.jpg");
     up_down.saveImage("flip_top_to_bottom mario.jpg");

 return 0 ;
}