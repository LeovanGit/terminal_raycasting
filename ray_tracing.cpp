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

    Box box = {-0.3, 0.3}; // cube
    // Box box = {{-0.3}, {0.5, 0.3, 0.3}}; // parallelepiped

    vector2 xy = 0;

    // static light
    vector3 point_light = vector3 (-0.5, -0.5, -0.5);
    vector3 camera = 0;
    vector3 ray = 0;

    int angle = 0;

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
                ray = rotate_z(ray, 13 * 180 / 3.14 ); 
                ray = rotate_x(ray, 13 * 180 / 3.14 ); 

                camera = vector3(0, 0, -1.5);
                camera = rotate_y(camera, angle * 0.05);       
                camera = rotate_z(camera, 13 * 180 / 3.14 ); 
                camera = rotate_x(camera, 13 * 180 / 3.14 ); 

                vector3 normal = 0;
                // i - intersection
                vector2 i_distances = box.is_intersect(camera, ray, normal);
                if (i_distances.x > 0)
                {
                    vector3 i_point = camera + ray * i_distances.x;
                    float cosa = dot_product(ray, normal);
                    cosa *= 15;
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
