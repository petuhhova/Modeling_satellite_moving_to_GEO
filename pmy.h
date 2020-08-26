#ifndef PMY_H
#define PMY_H

#include <QWidget>
#include "func.h"
#include "vector.h"
#include <QThread>
#include <QMutex>
#include <QTimer>

namespace Ui {
class pmy;
}

class pmy : public QWidget
{
    Q_OBJECT

public:
    explicit pmy(QWidget *parent = 0);
    ~pmy();
    func *f;// элемент класса подсчета методом рунге-кутты
    float t;
    float dt=30;
    float tactive=0;
    float forse=20000;
    float tstep=500;
    float mstep=500;
    float mepsilon=50;
    float mpol=0;
    int stepcounter=1;
    QPixmap draw;
    QImage image;
    QThread *thr1;
    QThread *thr2;
    QVector<QPointF> *polypoints;
    vector *U;
    std::thread t1;
    QMutex *m1;
    QThread* th;
    QTimer* timer;
    QString s;
    bool is_paused;
    bool is_stopped;


private:
    Ui::pmy *ui;
signals:
   void started();
   void stepdone();
   void paused();
   void stopped();
   void dostep();

public slots:
    //void calc();
    void startcalc();
    void stopcalc();
    void docalc();
    void pause();
    void isPaused();
    void setForse();
    void setMass();
    void quick();
    void setdt5();
    void setdt10();
    void setdt30();
    void save();
};

#endif // PMY_H
