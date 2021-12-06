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
    
    void exchange(float & a, float & b)
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

        if (t1.x > t2.x) exchange(t1.x, t2.x);
        if (t1.y > t2.y) exchange(t1.y, t2.y);
        if (t1.z > t2.z) exchange(t1.z, t2.z);

        float t_near = fmax(fmax(t1.x, t1.y), t1.z);
        float t_far = fmin(fmin(t2.x, t2.y), t2.z);

        // bad code :(
        if (t_near == t1.x) normal = {1, 0, 0};
        else if (t_near == t1.y) normal = {0, 1, 0};
        else if (t_near == t1.z) normal = {0, 0, 1};

        if (t_far < 0 || t_near > t_far) return -1;
        return vector2(t_near, t_far);
    }
};

#endif
