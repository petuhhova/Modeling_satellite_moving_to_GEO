#include "pmy.h"
#include <QApplication>
#include <QPixmap>
#include <QPaintDevice>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    pmy w;
    w.show();
    //QPixmap screen;
    //screen = QPixmap::grabWindow(QApplication::desktop()->winId());
    //screen.save("D:\picture.jpg");

    return a.exec();
}
