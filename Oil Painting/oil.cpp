#include <iostream>
#include "../Image_Class.h"

using namespace std;

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

int main() {
    string inputFilename;

    cout << "Enter the input image filename: ";
    cin >> inputFilename;

    Image image(inputFilename);

    oilPainting(image);


    string outputFilename;

    cout << "Enter the output image filename: ";
    cin >> outputFilename;

    image.saveImage(outputFilename);

    cout << "Oil Painting filter applied successfully!\n";

    return 0;
}