#include <iostream>
#include "../Image_Class.h"

using namespace std;

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

int main() {
    string inputFilename;

    cout << "Enter the input image filename: ";
    cin >> inputFilename;

    Image image(inputFilename);

    purpleEffect(image);

    string outputFilename;

    cout << "Enter the output image filename: ";
    cin >> outputFilename;

    image.saveImage(outputFilename);

    cout << "Purple effect applied successfully!\n";

    return 0;
}