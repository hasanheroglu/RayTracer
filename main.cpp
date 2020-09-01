#include <iostream>
#include "vector3.h"
#include "matrix4.h"

typedef Vec3<float> Vec3f;
typedef Mat4<float> Mat4f;

int main()
{
    Vec3f v1(1.2f, 1.6f, 1.8f);
    Vec3f v2;
    Vec3f v3(5.1f);
    
    v1.print();
    v2.print();
    v3.print();
    v3 += v1; 
    v2 -= v1;
    v2.print();
    v3.print();
    Vec3f v4 = v1 * v3;
    v4.print();
    v1 *= v3;
    v1.print();
    Vec3f v5(3.0f, 4.0f, 0.0f);
    v5.normalize().print();
    std::cout<<"v5 norm: "<<v5.norm()<<std::endl;

    Mat4f m1(5.0f);
    m1.print();
    Mat4f m2(0.0f, 2.0f, 3.0f, 4.0f,
             2.0f, 6.0f, 7.0f, 8.0f,
             4.0f, 5.0f, 3.0f, 2.0f,
             0.0f, 1.0f, 2.0f, 3.0f);
        
    Mat4f m3(3.0f);

    (m3*3).print();
    (m1-m3).print();
    m1 -= m2;
    m1.print();
    m1 += m2;
    m1.print();
}