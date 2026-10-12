QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    ../Downloads/CS213-2026-2027-Assignment1-v4/CS213-2026-2027-Assignemnt1-LibraryAndExample/CS213-2026-2027-Assignemnt1-LibraryAndExample/libaries/Image_Class.h \
    ../Downloads/CS213-2026-2027-Assignment1-v4/CS213-2026-2027-Assignemnt1-LibraryAndExample/CS213-2026-2027-Assignemnt1-LibraryAndExample/libaries/stb_image.h \
    ../Downloads/CS213-2026-2027-Assignment1-v4/CS213-2026-2027-Assignemnt1-LibraryAndExample/CS213-2026-2027-Assignemnt1-LibraryAndExample/libaries/stb_image_write.h \
    Filters.h \
    mainwindow.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
