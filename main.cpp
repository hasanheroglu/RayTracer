#include <iostream>
#include "vector3.h"

typedef Vec3<float> Vec3f;

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

    std::cout<<"hello world"<<std::endl;
}