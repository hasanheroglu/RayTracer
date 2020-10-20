#include "vector3.h"

#ifndef MATERIAL_H
#define MATERIAL_H
class Material{
    public:
        Material(): ambientColor(1.0f), diffuseColor(1.0f), specularColor(1.0f), shininess(1.0f){};
        Material(Vec3f ambientColor, Vec3f diffuseColor, Vec3f specularColor, float shininess): ambientColor(ambientColor), diffuseColor(diffuseColor), specularColor(specularColor), shininess(shininess){}

        Vec3f getAmbientColor(){ return ambientColor; }
        Vec3f getDiffuseColor(){ return diffuseColor; }
        Vec3f getSpecularColor(){ return specularColor; }
        float getShininess(){ return shininess; } 
        
    private:
        Vec3f ambientColor, diffuseColor, specularColor;
        float shininess;
};
#endif