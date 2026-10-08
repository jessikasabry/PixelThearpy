# include "Image_Class.h"
# include <iostream>
using namespace std ;

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

int main(){
 
    string image_name ;

    cout<< "Enter your image name :";
    cin >> image_name;
    
    Image my_image( image_name);
    increase_brightness(my_image);

    my_image.saveImage("lighting_photo.jpg");

    cout<< "lighting filter applied successfully ";

    return 0 ;
}