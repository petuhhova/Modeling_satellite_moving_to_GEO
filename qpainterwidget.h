
#ifndef QPAINTERWIDGET_H
#define QPAINTERWIDGET_H

#include <QWidget>
#include <QVector>
#include <cmath>

class QPaintEvent;

class QPainterWidget : public QWidget
{
    Q_OBJECT
public:
    QPainterWidget(QWidget * parent = 0);
    QPixmap draw;
    QImage image,earth=QImage("D:/earth.png"),sky=QImage("D:/sky.png"),sat=QImage("D:/sat.png");
    double minx=-43000000,miny=-43000000,maxx=43000000,maxy=43000000;
    double xscale,yscale;
    double stepx, stepy;
    QVector<QPointF> polyPoints1;
    QVector<QPointF> polyPoints2;
    //void mousePressEvent(QMouseEvent *event);
    double  razbienie(double min,double max,double n, int* i);
private:
    std::string name;
public slots:
    void save();
    //void graph();
signals:
    void repainted();
protected:
    void paintEvent(QPaintEvent*);
};

#endif // QPAINTWIDGET_H
