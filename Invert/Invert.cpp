#include <iostream>
#include "../Image_Class.h"

using namespace std;

void invertImage(Image& image){
    for (int i = 0; i < image.width; i++) {
        for (int j = 0; j < image.height; j++) {
            for (int c = 0; c < 3; c++) {
                image.getPixel(i, j, c) = 255 - image.getPixel(i, j, c);
            }
        }
    }
}

int main () {
    string filename;
    
    cout << "Enter the filename of the image";
    cin >> filename;
    
    Image image(filename);
    
    invertImage(image);

    cout << "Enter the output filename";
    cin >> filename;

    image.saveImage(filename);

    return 0;
}