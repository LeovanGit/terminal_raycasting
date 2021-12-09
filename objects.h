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
