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

    Plane v_plane = {{0, 0, -1}, 0}; // vertical
    Plane g_plane = {{0, -1, 0}, 0}; // horizontal

    vector2 xy = 0;

    // static light
    vector3 point_light = vector3(-0.5, -1, -0.5).normalize();
    vector3 camera = 0;
    vector3 ray = 0;

    float cosa = 2; // unreal value
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
                ray = rotate_x(ray, -45 * 180 / 3.14);
                ray = rotate_y(ray, angle * 0.01);

                camera = vector3(0, 0, -1.5);
                camera = rotate_x(camera, -45 * 180 / 3.14);
                camera = rotate_y(camera, angle * 0.01);

                // i - intersection
                float i_distance_v = v_plane.is_intersect(camera, ray);
                float i_distance_g = g_plane.is_intersect(camera, ray);

                vector3 i_point_v = camera + ray * i_distance_v;
                vector3 i_point_g =  camera + ray * i_distance_g;

                if (i_distance_v > 0 && i_distance_v < i_distance_g - 0.001 &&
                    i_point_v < vector3(v_plane.d) + 0.5 &&
                    i_point_v > vector3(v_plane.d) - 0.5)
                {
                    cosa = dot_product(point_light, v_plane.normal);
                }                
                else if (i_distance_g > 0 &&
                         i_point_g < vector3(g_plane.d) + 0.5 &&
                         i_point_g > vector3(g_plane.d) - 0.5)
                {
                    cosa = dot_product(point_light, g_plane.normal);
                }
                
                if (cosa < 2)
                {
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
