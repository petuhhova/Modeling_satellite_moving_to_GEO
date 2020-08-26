#include "vector.h"
#include "math.h"


vector::vector(float ro, float fi, float v, float omega, float m)
    :ro(ro), fi(fi), v(v), omega(omega), m(m)
{speed=(pow(ro*omega*ro*omega+v*v,0.5));}
vector::vector()
{}
/*vector vector::vector(){
       x = 0;
       y = 0;
       vx = 0;
       vy = 0;
   }
vector vector::vector(float ax, float ay, float avx, float avy){
       x = ax;
       y = ay;
       vx = avx;
       vy = avy;
   }
};*/
vector vector::operator+(vector b){
   vector c;
   c.ro = ro + b.ro;

   c.fi = fi + b.fi;
    c.v = v + b.v;
     c.omega = omega + b.omega;
      c.m = m + b.m;
   return(c);
}
vector vector::operator-(vector b){
   vector c;
   c.ro = ro - b.ro;

   c.fi = fi - b.fi;
    c.v = v - b.v;
     c.omega = omega - b.omega;
      c.m = m - b.m;

   return(c);
}
/*vector vector::operator*(vector b){
   vector c;
   c.x = a * b.x;
   c.y = a * b.y;
   c.vx = a * b.vx;
   c.vy = a * b.vy;
   return(c);
}*/// чет там какая -то лажа с коммутативностью,  будем умножать только вектор на число
vector vector::operator*(float a){
   vector c;
   c.ro = a * ro;

   c.fi = a * fi;
    c.v = a * v;
     c.omega = a * omega;
      c.m = a * m;

   return(c);
}
vector vector::operator*(double a){
   vector c;
   c.ro = a * ro;

   c.fi = a * fi;
    c.v = a * v;
     c.omega = a * omega;
      c.m = a * m;
   return(c);
}
void vector::changespeed()
{
    speed=pow(ro*omega*ro*omega+v*v,0.5);
}

