INCLUDEPATH += /usr/local/include \
INCLUDEPATH += /usr/local/include/opencv \
INCLUDEPATH += /usr/local/include/opencv2
INCLUDEPATH += /usr/lib/arm-linux-gnueabihf/libv4l/v4l1compat.so

LIBS += -L/usr/local/lib \
     -lopencv_core \
     -lopencv_highgui \
     -lopencv_imgproc \
     -lopencv_videoio \
     -lopencv_imgcodecs \
     -lopencv_features2d \
     -lopencv_flann

SOURCES += \
        main.cpp \
    v4l2_con.cpp \
    detect_methods.cpp \
    img_detect.cpp \
    show_methods.cpp

HEADERS += \
    detect_methods.h \
    v4l2_con.h \
    show_methods.h
