#include "qpainterwidget.h"

#include <QPainter>
#include <QMouseEvent>
#include <cmath>
#include <cstdlib>
#include <fstream>
#include <string>
#include <sstream>

QPainterWidget::QPainterWidget(QWidget * parent) : QWidget(parent)
{
        // устанавливаем цвет фона
    QPalette Pal(palette());
    Pal.setColor(QPalette::Background, Qt::black);
     setAutoFillBackground(true);
    setPalette(Pal);

}
void QPainterWidget::save()
{
    draw=QPixmap(size());//объект для сохраненияскриншота
    render(&draw);//текщий виджет впиксмап
    //draw=grab(QRect(QPoint(0,0),QSize(100,100))); как вариант тоже работает
    image=draw.toImage();// в имейдж
    image.save("D:/picture.jpg");
}
double  QPainterWidget::razbienie(double min,double max,double n,int* i)
{
    double c;
    c=((max-min)/n);
    if (c<0)
        c=-c;
    int a;
    int j=0;
        while(c>=1.0)
        {
            c=c/10.0;
            j++;
        }

        while (c<1.0)
        {
            c=c*10.0;
            j--;
        }

    a=c;
    c=a;
    *i=j;
    c=c*pow(10,j);
    return c;
}

void QPainterWidget::paintEvent( QPaintEvent *) {
    QPainter p(this);// Создаём новый объект рисовальщика
    //p.drawImage(0,0,image); //отрисовываем предыдущую картинку

    QString text;
    p.setViewport(0,0,this->width(),this->height());//физические координаты
    //p.setWindow(0,0,this->width(),this->height());
    QFont newFont;
    newFont.setPointSizeF(10);
    //set font of application
    p.setFont(newFont);
    p.scale(1.0,-1.0);
    //p.setWindow(minx,-maxy,-minx+maxx,-miny+maxy);
    p.translate(QPointF(50.0,0));
    xscale=(this->width()-80.0)/(-minx+maxx);
    yscale=(this->height()-50.0)/(-miny+maxy);
    p.scale(xscale,yscale);
    p.translate(QPointF(-minx,-maxy));
    //левый верхний угол (minx,-maxy)
    QPen pen(Qt::white,1,Qt::DotLine);
    pen.setCosmetic(true);//чтоб не масштабировалась кисть
    p.setPen(pen);
    //создание сетки
    double x,y,n=9.0;
    int i,j;
    int c;
     p.drawImage(QRectF(-43000000,-43000000,86000000,86000000),sky);
    p.drawImage(QRectF(-18100000,-12300000,33800000,24400000),earth);
    p.drawEllipse(QPoint(0,0),6137000,6137000);
    stepx=razbienie(minx,maxx,12.0,&i);
    stepy=razbienie(miny,maxy,8.0,&j);
    //stepx=10.0;
    //stepy=10.0;
    //p.scale(1/xscale,1/yscale);
    //p.drawText(QPointF(minx*xscale,maxy*yscale),QString::number(minx));
    //p.scale(xscale,yscale);
    //p.setPen(pen);

    int f=0;
    if ((minx<0.0)&&(maxx>0.0))
    {
        x=0.0;
        while (x>minx)
        {
            p.drawLine(QLineF(x,miny,x,maxy));
            text=QString::number(x/1000);
          p.scale(1/xscale,-1/yscale);
          if (f==1)
          {
            p.drawText(QPointF(x*xscale,(-miny)*yscale+30.0),text);
            f=0;
          }
          else
              f=1;
            p.scale(xscale,-yscale);
            x=x-stepx;
        }
        x=0.0+stepx;
        while (x<maxx)
        {
            p.drawLine(QLineF(x,miny,x,maxy));
            text=QString::number(x/1000);
            p.scale(1/xscale,-1/yscale);
            if (f==1)
            {
              p.drawText(QPointF(x*xscale,(-miny)*yscale+30.0),text);
              f=0;
            }
            else
                f=1;
            p.scale(xscale,-yscale);
            x=x+stepx;
        }
    }
        else
    {
       x=minx/pow(10.0,i);
       c=x;
       x=c;
       x=x*pow(10.0,i);
       while (x<maxx)
       {
           {
               p.drawLine(QLineF(x,miny,x,maxy));
               text=QString::number(x/1000);
               p.scale(1/xscale,-1/yscale);
               if (f==1)
               {
                 p.drawText(QPointF(x*xscale,(-miny)*yscale+30.0),text);
                 f=0;
               }
               else
                   f=1;
               p.scale(xscale,-yscale);
               x=x+stepx;
           }
       }


    }
    if ((miny<0.0)&&(maxy>0.0))
    {
        y=0.0;
        while (y>miny)
        {
            p.drawLine(QLineF(minx,y,maxx,y));
            text=QString::number(y/1000);
            p.scale(1/xscale,-1/yscale);
            p.drawText(QPointF((minx)*xscale-40.0,-y*yscale),text);
           p.scale(xscale,-yscale);
            y=y-stepy;
        }
        y=0.0+stepy;
        while (y<maxy)
        {
            p.drawLine(QLineF(minx,y,maxx,y));
            text=QString::number(y/1000);
            p.scale(1/xscale,-1/yscale);
            p.drawText(QPointF((minx)*xscale-40.0,-y*yscale),text);
            p.scale(xscale,-yscale);
            y=y+stepy;
        }
    }
        else
    {
       y=miny/pow(10.0,j);
       c=y;
       y=c;
       y=y*pow(10.0,j);
       while (y<maxy)
       {
           {
               p.drawLine(QLineF(minx,y,maxx,y));
               text=QString::number(y/1000);
               p.scale(1/xscale,-1/yscale);
               p.drawText(QPointF((minx)*xscale-40.0,-y*yscale),text);
               p.scale(xscale,-yscale);
               y=y+stepy;
           }
       }


    }

    pen.setColor(Qt::white);
    pen.setStyle(Qt::SolidLine);
    pen.setWidth(2);
    p.setPen(pen);
    p.drawLine(QLineF(minx,0.0,maxx,0.0));
    p.drawLine(QLineF(0.0,miny,0.0,maxy));
    p.drawLine(QLineF(minx,miny,maxx,miny));
    p.drawLine(QLineF(minx,miny,minx,maxy));
    //text="f(x)";
    p.scale(1/xscale,-1/yscale);
    newFont.setPointSizeF(20);
    p.setFont(newFont);
    //p.drawText(QPointF((minx)*xscale-80.0,((-maxy-miny)/2.0)*yscale),text);
    //text="x";
    //p.drawText(QPointF((maxx+minx)/2.0*xscale,(-miny)*yscale+40.0),text);
    p.scale(xscale,-yscale);
    pen.setStyle(Qt::DotLine);
    p.setPen(pen);
    p.drawEllipse(QPoint(0,0),42164137,42164137);
    //ура, нарисовалисетку, подписи и тп
    pen.setColor(Qt::red);
    pen.setWidth(2);
    p.setPen(pen);
    p.drawPolyline(polyPoints1);
    pen.setColor(Qt::green);
    pen.setWidth(2);
    p.setPen(pen);
    p.drawPoints(polyPoints2);
    if (polyPoints1.isEmpty()==false)
    {
        QPointF point=QPointF(polyPoints1.last());
    p.drawImage(QRectF(point.x()-5000000,point.y()-5000000,10000000,10000000),sat);
    }
    emit repainted();
    // Рисование линии


}

