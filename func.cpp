#include "func.h"
#include <fstream>
#include <iostream>
#include <math.h>
#include <QObject>


#define INFINIT 100000
#include "vector.h"

func::func(float forse1, float dt1):forse(forse1), dt(dt1)
{
    U=new vector;
    t=new float;
}

vector func::F(vector U,float t)//производная
{
       vector res;
       res.ro = U.v;
       res.fi=U.omega;
       res.v=U.ro*U.omega*U.omega-gamma*mass/U.ro/U.ro+forse*U.v/U.m*pow(U.v*U.v+U.ro*U.ro*U.omega*U.omega,-0.5);
       res.omega=-2*U.v*U.omega/U.ro+forse*U.omega/U.m*pow(U.v*U.v+U.ro*U.ro*U.omega*U.omega,-0.5);
       res.m=-mu*forse;
       //res.vx =-U.vx*U.vx*U.x/l/l- 9.81*(U.x*U.x/l/l-1.0);
       //res.fi=-9.81/l*sin(U.x);
       return(res);
}
void func::runge()
{
       vector k1,k2,k3,k4;
       double half=pow(6.0,-1.0);//для деления на 6
       k1 = F(*U,*t)*dt;
       k2 = F(*U + k1*0.5, *t+(0.5)*dt)*dt;
       k3 = F(*U + k2*0.5, *t+(0.5)*dt)*dt;
       k4 = F(*U + k3, *t+dt)*dt;
       *U =*U + (k1 + k2*2.0 + k3*2.0 + k4)*1.0*half;//
       *t += dt;
       U->changespeed();
       if ((U->v<=10)&&(U->v>=-10))
           emit startactive();
       emit finished();
}
void func::ex()
{
     int i=0;
    i++;
    emit finished();
}
