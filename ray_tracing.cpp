#include <iostream>
#include <unistd.h>
#include <cmath>
#include <ncurses.h>

#include "./vectors.h"
#include "./objects.h"

int height, width;
char gradient[] = ".:!/r(1l49ZHW8$@";
int g_size = 15;

int main()
{
    initscr();

    noecho();
    curs_set(0);

    getmaxyx(stdscr, height, width);

    float distortion = (8.0 / 16) * (width / height);

    Sphere sphere = {0.4, vector3(-0.6, 0, 0)};
    Box box = {vector3(0.2, 0.4, 0.4), vector3(1, -0.4, -0.4)};
    Plane plane = {vector3(0, -1, 0), 1};

    vector2 xy = 0;

    // static light
    vector3 point_light = vector3(1, -1, 0.5).normalize();
    vector3 camera = 0;
    vector3 ray = 0;

    float cosa = 2;
    int angle = 0;

    float min_distance = 100000; // render distance
    vector3 normal = 0;

    float k = 1; // что бы свет на плоскости и на кубе по разному немного был
    // ато сливается, чисто косметическое

    while (true)
    {
        for (int i = 0; i < width; ++i)
        {
            for (int j = 0; j < height; ++j)
            {
                xy = (vector2((float)i, (float)j) / vector2(width, height)) 
                    * 2.0f - 1.0f; // [-1.0; 1.0]
                xy.x *= distortion;
            
                xy = xy / 2.0f; // FOV

                ray = vector3(xy.x, xy.y, 1).normalize();                               
                ray = rotate_x(ray, 15 * 180 / 3.14);
                ray = rotate_y(ray, angle * 0.01);

                camera = vector3(0, 0, -2);
                camera = rotate_x(camera, 15 * 180 / 3.14);
                camera = rotate_y(camera, angle * 0.01);

                k = 1;
                min_distance = 100000;

                float i_distance = sphere.is_intersect(camera, ray).x;

                if (i_distance > 0)
                {
                    min_distance = i_distance;
                    normal = (camera + ray * i_distance) - sphere.center;
                }
                
                vector3 box_normal = 0;
                i_distance = box.is_intersect(camera,ray, box_normal).x;

                if (i_distance > 0 && i_distance < min_distance)
                {
                    min_distance = i_distance;
                    normal = box_normal;
                }

                i_distance = plane.is_intersect(camera, ray);

                if (i_distance > 0 && i_distance < min_distance)
                {
                    min_distance = i_distance;
                    normal = plane.normal;
                    k = 0.8;
                }
                
                if (min_distance < 100000)
                {
                    cosa = dot_product(point_light, normal.normalize());
                    cosa *= 15 * k;
                    cosa = fmin(fmax(0, cosa), g_size);
                    mvaddch(j, i, gradient[int(cosa)]); 
                } else mvaddch(j, i, ' ');
            }
        }
        ++angle;
        usleep(20000);
        refresh();
    }
    endwin();
    return 0;
}
