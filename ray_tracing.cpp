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

    Sphere sphere = {0.5, {0, 0, 0}};

    vector2 xy = 0;

    // static light
    vector3 point_light = vector3 (-0.5, -0.5, -0.5);
    vector3 camera = 0;
    vector3 ray = 0;

    unsigned int angle = 0;

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
                ray = rotate_y(ray, angle * 0.05); 
                
                camera = vector3(0, 0, -1.5);
                camera = rotate_y(camera, angle * 0.05);       
                
                // spinning in xz plane light
                // vector3 point_light = vector3(cos(t * 0.001), 0, sin(t * 0.001)).normalize();
            
                // i - intersection
                vector2 i_distances = sphere.is_intersect(camera, ray).x;

                if (i_distances.x > 0)
                {
                    vector3 i_point = camera + ray * i_distances.x;
                    vector3 normal = (i_point - sphere.center).normalize();
                    float cosa = dot_product(normal, point_light);               
                    cosa *= 15;
                    cosa = fmin(fmax(0, cosa), g_size);

                    mvaddch(j, i, gradient[int(cosa)]);                
                }
                else mvaddch(j, i, ' ');
            }
        }
        ++angle;
        usleep(20000);
        refresh();
    }
    endwin();
    return 0;
}
