#ifndef OBJECTS_H
#define OBJECTS_H

#include <cmath>
#include "./vectors.h"

class Plane
{
public:
    vector3 normal;
    float d;

    float is_intersect(vector3 camera, vector3 ray)
    {
        return -(dot_product(camera, normal) + d) / dot_product(ray, normal);
    }
};

#endif
