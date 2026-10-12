============================================================
CS213 - Assignment 1 (Baby Photoshop) - GUI version
Faculty of Computing and AI, Cairo University
Supervisor: Dr. Mohammad El-Ramly
Section: S37, S38
============================================================

Team:
- Joussyana 20250167
- Jessika 20250171
- Salma 20250286
- Jana 20251105

------------------------------------------------------------
1. TOOLS USED
------------------------------------------------------------
- OS: macOS Tahoe 26.5.2 (Apple M4 Pro)
- Qt: 6.12.0
- Qt Creator: 20.0.2
- Compiler: Apple Clang (arm64)
- Build system / project file: qmake (BabyPhotoshop.pro)

------------------------------------------------------------
2. HOW TO SET UP AND RUN
------------------------------------------------------------
1. Extract the zip file to any folder.
2. Open Qt Creator and choose File > Open File or Project.
3. Select the project file: BabyPhotoshop.pro
4. Choose the kit: Qt 6.12.0 with Apple Clang (Desktop Qt 6.12.0 for macOS).
5. Make sure Image_Class.h, stb_image.h and stb_image_write.h are in
the same folder as the source files (they are included in the zip).
6. Press Build (Cmd+B on macOS, Ctrl+B on Windows/Linux), then
Run (Cmd+R on macOS, Ctrl+R on Windows/Linux).

------------------------------------------------------------
3. FILES IN THIS PROJECT
------------------------------------------------------------
- main.cpp : program entry point (starts the Qt application)
- CS213_A1_Part2_section37...cpp : main file with the team header (IDs,
section, work breakdown) and the links to the video
and the shared document
- mainwindow.h/.cpp : main window, buttons, dialogs, Load / Save / Undo
- mainwindow.ui : Qt Designer UI file of the main window
- Filters.h : implementation of the 18 filters
- Image_Class.h, stb_image.h, stb_image_write.h : image library headers
- BabyPhotoshop.pro : Qt project file
- Vedio Link.txt : link to the demo video and the shared document
- Documentation for the first part (.pdf) : documentation of Part 1
(the console version with the first 8 filters)

------------------------------------------------------------
4. HOW TO USE THE PROGRAM
------------------------------------------------------------
1. Click "Open image" and choose an image (png, jpg, jpeg, bmp, tga).
2. Click any filter button on the left side of the window.
Filters that need input (frame, flip, rotate, darken/lighten,
resize, crop, blur, merge, skew) open a dialog where you enter
the values. Darken/Lighten and Blur use a slider with a preview.
Use the scroll bar if the buttons do not all fit.
3. The result is shown in the center of the window.
4. Click "Undo" to go back to the previous version of the image
(one step back).
5. Click "Save image" to save the result. If no extension is typed,
.png is added automatically.

------------------------------------------------------------
5. NOTES
------------------------------------------------------------
- Load an image first, otherwise a warning message will appear.
- Loading a new image clears the Undo history.
- Merge asks for a second image and how to handle different sizes.
- Cancelling any dialog leaves the image unchanged.
- The demo video and the shared document links are in
Vedio Link.txt.

------------------------------------------------------------
6. LINKS
------------------------------------------------------------
Demo video:
https://drive.google.com/file/d/1Fs8vbdipveMggpzOStJiJqF2FHE7fphZ/view?usp=drivesdk

Shared document:
https://docs.google.com/document/d/1-69VafP2UQs76Mi1Y6DiV3kagUpeyqnrAhcvC6-qKr0/edit?usp=drivesdk

