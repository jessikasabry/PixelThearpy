#include <iostream>
#include "../Image_Class.h"

using namespace std;

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

int main() {
    string inputFilename;
    string outputFilename;

    cout << "Enter input image filename: ";
    cin >> inputFilename;

    Image image(inputFilename);

    int X, Y, W, H;

    while (true) {
        cout << "Enter X (Start column): ";
        cin >> X;
        
        cout << "Enter Y (Start row): ";
        cin >> Y;
        
        cout << "Enter W (Width): ";
        cin >> W;
        
        cout << "Enter H (Height): ";
        cin >> H;

        if (cin.fail()) {
            cout << "Invalid input. Please enter valid whole numbers.\n";
            cin.clear();
            cin.ignore(10000, '\n');
            continue;
        }
        
        if (X < 0 || Y < 0 || W <= 0 || H <= 0 ) {
            cout << "Invalid dimensions or starting points.\n";
            continue;
        }
        
        if (X + W > image.width || Y + H > image.height) {
            cout << "The crop area is outside the original image.\n";
            continue;
        }
        
        break;
    }

    Image croppedImage = cropImage(image, X, Y, W, H);

    cout << "Enter output filename: ";
    cin >> outputFilename;

    croppedImage.saveImage(outputFilename);

    cout << "Image cropped successfully!" << "\n";

    return 0;
}