#include <iostream>
#include <cmath>
#include "../Image_Class.h"

using namespace std;

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

                image.getPixel(i, j, c) = newValue;
            }
        }
    }
}

int main () {
    string filename;

    cout << "Enter the filename of the image: ";
    cin >> filename;

    Image image(filename);

    int level;

    cout << "Enter the level (0-100): ";
    cin >> level;

    while (level < 0 || level > 100) {
        cout << "Invalid level. Please enter a value between 0 and 100: ";
        cin >> level;
    }

    Darken_Lighten(image, level);

    string outputFilename;

    cout << "Enter the output filename: ";
    cin >> outputFilename;

    image.saveImage(outputFilename);

    return 0;
}