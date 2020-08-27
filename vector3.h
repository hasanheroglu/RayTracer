#include <iostream>
#include <cmath>

template <typename T>
class Vec3
{
    public:
        Vec3(): x(T(0)), y(T(0)), z(T(0)){};
        Vec3(T v): x(v), y(v), z(v){};
        Vec3(T x, T y, T z): x(x), y(y), z(z){};
        Vec3<T> operator +(const Vec3<T> &v){ return Vec3<T>(x+v.x, y+v.y, z+v.z); }
        Vec3<T>& operator +=(const Vec3<T> &v){ x+=v.x; y+=v.y; z+=v.z; return *this; }
        Vec3<T> operator -(){ return Vec3<T>(-x, -y, -z); }
        Vec3<T> operator -(const Vec3<T> &v){ return Vec3<T>(x-v.x, y-v.y, z-v.z); }
        Vec3<T>& operator -=(const Vec3<T> &v){ x-=v.x; y-=v.y; z-=v.z; return *this; }
        Vec3<T> operator *(const Vec3<T> &v) { return Vec3<T>(x*v.x, y*v.y, z*v.z); }
        Vec3<T>& operator *=(const Vec3<T> &v) { x*=v.x; y*=v.y; z*=v.z; return *this; }
        T norm2() { return x*x + y*y + z*z; }
        T norm() { return sqrt(norm2()); }
        Vec3<T>& normalize()
        { 
            if(norm2() > 0)
            {
                T invNorm = 1 / norm();
                x *= invNorm; y *= invNorm; z *= invNorm;
            }

            return *this;
        }

        void print(){ std::cout<<"x: "<<x<<" y: "<<y<<" z: "<<z<<std::endl; }
    private: 
        T x, y, z;
}; 
 