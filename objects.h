#ifndef OBJECTS_H
#define OBJECTS_H

#include <cmath>
#include "./vectors.h"

class Sphere
{
public:
    float radius;
    vector3 center;
    
    // returns distances from camera to intersect points
    vector2 is_intersect(vector3 camera, vector3 ray)
    {
        vector3 v = center - camera;
        float abs_v = v.module();
        float a = projection(v, ray);
        float sq_l = abs_v * abs_v - a * a;
        if (sq_l > radius * radius) return vector2(-1, -1);
        float x = sqrt(radius*radius - sq_l);
        return vector2(a - x, a + x);
    }
};

#endif
