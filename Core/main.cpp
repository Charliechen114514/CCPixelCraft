#include <QApplication>
#include "CCImageMainWindow.h"
#include <opencv2/opencv.hpp>
int main(int argc, char *argv[]) {
    QApplication      a(argc, argv);
    CCImageMainWindow w;
    w.show();
    return a.exec();
}
