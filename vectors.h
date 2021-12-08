#ifndef VECTORS_H
#define VECTORS_H

#include <cmath>

class vector3
{
public:
    float x = 0;
    float y = 0;
    float z = 0;

    vector3()
    {
        x = 0;
        y = 0;
        z = 0;
    }
    
    vector3(float t)
    {
        x = t;
        y = t;
        z = t;
    }

    vector3(float x_, float y_, float z_)
    {
        x = x_;
        y = y_;
        z = z_;
    }

    float module()
    {
        return sqrt(x * x + y * y + z * z);
    }

    vector3 normalize()
    {
        float l = module();
        return {x / l, y / l, z / l};
    }

    vector3 operator+(vector3 const& other)
    {
        return {x + other.x, y + other.y, z + other.z};
    }

    vector3 operator-(vector3 const& other)
    {
        return {x - other.x, y - other.y, z - other.z};
    }

    vector3 operator-() 
    {
        return {-x, -y, -z};
    }

    vector3 operator*(vector3 const& other)
    {
        return {x * other.x, y * other.y, z * other.z};
    }

    vector3 operator/(vector3 const& other)
    {
        return {x / other.x, y / other.y, z / other.z};
    }

    bool operator<(vector3 const& other)
    {
        return (x < other.x && y < other.y && z < other.z);
    }

    bool operator>(vector3 const& other)
    {
        return (x > other.x && y > other.y && z > other.z);
    }

};

class vector2
{
public:
    float x = 0;
    float y = 0;

    vector2()
    {
        x = 0;
        y = 0;
    }

    vector2(float t)
    {
        x = t;
        y = t;
    }

    vector2(float x_, float y_)
    {
        x = x_;
        y = y_;
    }

    float module()
    {
        return sqrt(x * x + y * y);
    }

    vector2 normalize()
    {
        float l = module();
        return {x / l, y / l};
    }

    vector2 operator+(vector2 const& other)
    {
        return {x + other.x, y + other.y};
    }

    vector2 operator-(vector2 const& other)
    {
        return {x - other.x, y - other.y};
    }

    vector2 operator-() 
    {
        return {-x, -y};
    }

    vector2 operator*(vector2 const& other)
    {
        return {x * other.x, y * other.y};
    }

    vector2 operator/(vector2 const& other)
    {
        return {x / other.x, y / other.y};
    }
};

// =========================[ADDITIONAL FUNCTIONS]=========================

float distance(vector3 a, vector3 b)
{
    return sqrt((a.x - b.x) * (a.x - b.x) +
                (a.y - b.y) * (a.y - b.y) +
                (a.z - b.z) * (a.z - b.z));
}

float dot_product(vector3 a, vector3 b)
{
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

// project vector a on vector b
float projection(vector3 a, vector3 b)
{
    return dot_product(b.normalize(), a);
}


float distance(vector2 a, vector2 b)
{
    return sqrt((a.x - b.x) * (a.x - b.x) +
                (a.y - b.y) * (a.y - b.y));
}

float dot_product(vector2 a, vector2 b)
{
    return a.x * b.x + a.y * b.y;
}

// =========================[TRANSFORMATION MATRIX]=========================

// rotation in yz
vector3 rotate_x(vector3 a, float angle)
{
    vector3 b = a;
    b.y = a.y * cos(angle) - a.z * sin(angle);
    b.z = a.y * sin(angle) + a.z * cos(angle);
    return b;
}

// rotation in xz
vector3 rotate_y(vector3 a, float angle)
{
    vector3 b = a;
    b.x = a.x * cos(angle) - a.z * sin(angle);
    b.z = a.x * sin(angle) + a.z * cos(angle);
    return b;
}

// rotation in xy
vector3 rotate_z(vector3 a, float angle)
{
    vector3 b = a;
    b.x = a.x * cos(angle) - a.y * sin(angle);
    b.y = a.x * sin(angle) + a.y * cos(angle);
    return b;
}

#endif
