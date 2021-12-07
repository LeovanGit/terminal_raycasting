#ifndef OBJECTS_H
#define OBJECTS_H

#include <cmath>
#include "./vectors.h"

class Box
{
public:
    // two points on one diagonal which define a box
    vector3 A;
    vector3 B;
    
    void swap(float & a, float & b)
    {
        float t = a;
        a = b;
        b = t;
    }

    vector2 is_intersect(vector3 camera, vector3 ray, vector3 & normal)
    {
        vector3 t1 = {(A.x - camera.x) / ray.x,
                      (A.y - camera.y) / ray.y,
                      (A.z - camera.z) / ray.z};

        vector3 t2 = {(B.x - camera.x) / ray.x,
                      (B.y - camera.y) / ray.y,
                      (B.z - camera.z) / ray.z};

        if (t1.x > t2.x) swap(t1.x, t2.x);
        if (t1.y > t2.y) swap(t1.y, t2.y);
        if (t1.z > t2.z) swap(t1.z, t2.z);

        float t_near = fmax(fmax(t1.x, t1.y), t1.z);
        float t_far  = fmin(fmin(t2.x, t2.y), t2.z);

        // need another algorithm to calculate normals
        vector3 i_point = camera + ray * t_near;
        if      (t_near == t1.x && std::abs(i_point.x - A.x) < 0.1) normal = {-1, 0, 0};
        else if (t_near == t1.x && std::abs(i_point.x - B.x) < 0.1) normal = {1, 0, 0};
        else if (t_near == t1.y && std::abs(i_point.y - A.y) < 0.1) normal = {0, 1, 0};
        else if (t_near == t1.y && std::abs(i_point.y - B.y) < 0.1) normal = {0, -1, 0};
        else if (t_near == t1.z && std::abs(i_point.z - A.z) < 0.1) normal = {0, 0, 1};
        else if (t_near == t1.z && std::abs(i_point.z - B.z) < 0.1) normal = {0, 0, -1};

        if (t_far < 0 || t_near > t_far) return -1;
        return vector2(t_near, t_far);
    }
};

#endif
