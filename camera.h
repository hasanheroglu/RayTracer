#include "vector3.h"

#ifndef CAMERA_H
#define CAMERA_H

class Camera {
    public:
        Camera(): origin(Vec3f(0.0f)), forward(Vec3f(0.0f, 0.0f, 1.0f)), up(Vec3f(0.0f, 1.0f, 0.0f)), near(1.0f), far(100.0f), width(500), height(500), fov(1.285f) {};
        Camera(Vec3f origin, Vec3f forward, Vec3f up, float near, float far, int width, int height, float fov): origin(origin), forward(forward), up(up), near(near), far(far), width(width), height(height), fov(fov) {}; 
        Vec3f getOrigin () const { return origin; }
        Vec3f getForward () const { return forward; }
        Vec3f getUp () const { return up; }
        float getNear () const { return near; }
        float getFar () const { return far; }
        int getWidth () const { return width; }
        int getHeight () const { return height; }
        float getFOV () const { return fov; }  
    private:
        Vec3f origin;
        Vec3f forward;
        Vec3f up;
        float near;
        float far;
        int width;
        int height;
        float fov;
};

#endif