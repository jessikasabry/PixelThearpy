#include <iostream>
#include <cmath>
#include "../Image_Class.h"

using namespace std;

void darkenImage(Image& image, int level) {
    for (int i = 0; i < image.width; i++) {
        for (int j = 0; j < image.height; j++) {
            for (int c = 0; c < 3; c++) {
               
               int p = image.getPixel(i, j, c);
               double t = level / 100.0;
               double factor = pow(0.05, t);
               int newValue = p * factor;
               
               if (newValue < 0) {
                newValue = 0;
               } 

                image.getPixel(i, j, c) = newValue;
            }
        }
    }
}

void lightenImage(Image& image, int level) {
    for (int i = 0; i < image.width; i++) {
        for (int j = 0; j < image.height; j++) {
            for (int c = 0; c < 3; c++) {  
                int p = image.getPixel(i, j, c);
                int newValue = p *(1 + level / 100.0);

                if (newValue > 255) {
                    newValue = 255;
                }

                image.getPixel(i, j, c) = newValue;
            }
        }
    }
}

int main () {
    string filename;

    cout << "Enter the filename of the image; ";
    cin >> filename;

    Image image(filename);

    int choice;

    cout << "Enter 1 for Darken or 2 for Lighten: ";
    cin >> choice;

    while (choice != 1 && choice != 2) {
        cout << "Invalid choice. Enter 1 for Darken or 2 for Lighten: ";
        cin >> choice;
    }

    int level;

    cout << "Enter the level (0-100): ";
    cin >> level;

    while (level < 0 || level > 100) {
        cout << "Invalid level. Please enter a value between 0 and 100: ";
        cin >> level;
    }

    if (choice ==1) {
        darkenImage(image, level);
    }
    else {
        lightenImage(image, level);
    }

    string outputFilename;

    cout << "Enter the output filename: ";
    cin >> outputFilename;

    image.saveImage(outputFilename);

    return 0;
}