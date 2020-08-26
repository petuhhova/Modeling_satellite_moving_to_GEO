#ifndef FUNC_H
#define FUNC_H

#include <fstream>
#include <vector.h>
#include <QWidget>
#include <thread>
#include <math.h>

class func:public QObject
{
    Q_OBJECT
public:
    explicit func(float forse, float dt);
    //~func();
signals:
    void finished();
    void startactive();
private:
    float dt;

   // float const mu=3.07*pow(10,-3);
    float const mu=0.000307;
public:
    float const gamma=6.67428*pow(10,-11);
    float const mass=5.9736*pow(10,24);
    //vector u;
    float forse;
    vector *U;
    float *t;
    vector F(vector U,float t);
public slots:
    void runge();
    void ex();
    //double angle(float *t, vector *U);
};

#endif // FUNC_H
