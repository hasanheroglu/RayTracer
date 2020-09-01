#include <iostream>
#include <stdio.h>
#include "vector3.h"
#include "matrix4.h"

typedef Vec3<float> Vec3f;
typedef Mat4<float> Mat4f;

int main()
{
    Vec3f v1(1.2f, 1.6f, 1.8f);
    Vec3f v2;
    Vec3f v3(5.1f);
    
    printf("v1 dot v2 = %f\nv1 dot v3 =  %f\n", v1.dot(v2), v1.dot(v3));


}