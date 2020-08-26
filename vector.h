#ifndef VECTOR_H
#define VECTOR_H

#include <QWidget>
#include <thread>


class vector{
    public:
    float ro,fi,v,omega,m;
    float speed;
    vector();//создание 0го вектора
    vector(float ro, float fi, float v, float omega,float m);//инициализация, нужна ли?
    vector operator+(vector b);
    vector operator-(vector b);
    //vector operator*(vector b);
    vector operator*(float a);
    vector operator*(double a);
    void changespeed();
};

#endif // VECTOR_H
