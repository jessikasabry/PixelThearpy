// FILTER 9;

# include "Image_Class.h"
# include <iostream>
using namespace std ;


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



void merge_images(Image &image1, Image &image2){

    int width, height;
    if (image1.width==image2.width && image1.height==image2.height){

        width=image1.width; height=image1.height;
    }

    else{

        int choice;

        cout<<" the two_images have different sizes \n";
        cout << "choose one of two options\n";
        cout<< " choose 1  resize to the beggist size\n";
        cout<<" choose 2  merge common_area\n";

        cin>> choice;

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

        cout<<"invalid choice";
    }

      

    Image merged_photo(width,height);
     for (int x =0 ; x < width;++x){

        for (int y=0; y< height; ++y){

            for(int color=0; color <3; ++color){

                merged_photo(x,y,color)=(image1(x,y,color)+image2(x,y,color))/2;

            
            }
        }
     }

     merged_photo.saveImage("merged photo.jpg");
    }
}


int main(){


    string name1, name2;
    
     cout<<"Enter first image name:";

     cin>> name1;

     cout<< "enter seconde image name:";

     cin>> name2;

     Image image1(name1);
     Image image2(name2);

     merge_images(image1, image2);

     cout<<" the two images are successfully merged !!";
        
     return 0 ;

}