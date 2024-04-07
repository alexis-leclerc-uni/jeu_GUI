#include "ui/menuwindow.h"
#include <QApplication>

int main(int argc, char* argv[])
{
    QApplication a(argc, argv);
    MenuWindow w;

    return a.exec();
}