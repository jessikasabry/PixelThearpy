#include <iostream>
#include "../Image_Class.h"
using namespace std;


void saveImage(Image& image, string& currentFilename) {
    int choice;

    cout << "Do you want to save on the same file?\n";
    cout << "1. Yes\n";
    cout << "2. No, save with a new file name\n";
    cout << "Enter your choice: ";
    cin >> choice;

    while (choice != 1 && choice != 2) {
        cout << "Invalid choice. Enter 1 or 2: ";
        cin >> choice;
    }

    if (choice == 1) {
        image.saveImage(currentFilename);
        cout << "Image saved successfully.\n";
    }
    else {
        string newFilename;
        int format;

        cout << "Enter the new file name: ";
        cin >> newFilename;

        int dot = newFilename.find_last_of('.');
        if (dot != -1) {
            newFilename = newFilename.substr(0, dot);
        }

        cout << "Choose the file format:\n";
        cout << "1. JPG\n";
        cout << "2. PNG\n";
        cout << "3. BMP\n";
        cout << "4. TGA\n";
        cout << "Enter your choce: ";
        cin >> format;

        while (format < 1 || format > 4) {
            cout << "Invalid choice. Enter a number from 1 to 4: ";
            cin >> format;
        }

        if (format == 1) {
            newFilename += ".jpg";
        }
        else if (format == 2) {
            newFilename += ".png";
        }
        else if (format == 3) {
            newFilename += ".bmp";
        }
        else {
            newFilename += ".tga";
        }

        image.saveImage(newFilename);
        currentFilename = newFilename;

        cout << "Image saved successfully.\n";
    }
}

int main() {
    string filename;

    cout << "Enter the image name: ";
    cin >> filename;

    Image image(filename);

    saveImage(image, filename);

    return 0;
}