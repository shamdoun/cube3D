#include "cube3D.h"

extern int mapValues[10][21];

void move_up(t_player *p)
{
    double old_x;
    double old_y;

    old_x = p->x_p;
    old_y = p->y_p;

    p->x_p = p->x_p + cos(-p->angle * (M_PI / 180)) * 4;
    p->y_p = p->y_p + sin(-p->angle * (M_PI / 180)) * 4;


    if (mapValues[(int)floor((p->y_p - 20) / 80)][(int)floor((p->x_p) / 80)] == 1 || mapValues[(int)floor((p->y_p) / 80)][(int)floor((p->x_p + 20) / 80)] == 1 
        || mapValues[(int)floor((p->y_p) / 80)][(int)floor((p->x_p - 20) / 80)] == 1 || mapValues[(int)floor((p->y_p + 20) / 80)][(int)floor((p->x_p) / 80)] == 1
        || mapValues[(int)floor((p->y_p + 20) / 80)][(int)floor((p->x_p - 20) / 80)] == 1 || mapValues[(int)floor((p->y_p - 20) / 80)][(int)floor((p->x_p - 20) / 80)] == 1 ||
        mapValues[(int)floor((p->y_p - 20) / 80)][(int)floor((p->x_p + 20) / 80)] == 1 || mapValues[(int)floor((p->y_p + 20) / 80)][(int)floor((p->x_p + 20) / 80)] == 1)
    {
        p->x_p = old_x;
        p->y_p = old_y;
    }
}

void move_down(t_player *p)
{
    double old_x;
    double old_y;

    old_x = p->x_p;
    old_y = p->y_p;

    p->x_p = p->x_p + cos(-p->angle * (M_PI / 180)) * -4;
    p->y_p = p->y_p + sin(-p->angle * (M_PI / 180)) * -4;

    if (mapValues[(int)floor((p->y_p - 20) / 80)][(int)floor((p->x_p) / 80)] == 1 || mapValues[(int)floor((p->y_p) / 80)][(int)floor((p->x_p + 20) / 80)] == 1 
        || mapValues[(int)floor((p->y_p) / 80)][(int)floor((p->x_p - 20) / 80)] == 1 || mapValues[(int)floor((p->y_p + 20) / 80)][(int)floor((p->x_p) / 80)] == 1
        || mapValues[(int)floor((p->y_p + 20) / 80)][(int)floor((p->x_p - 20) / 80)] == 1 || mapValues[(int)floor((p->y_p - 20) / 80)][(int)floor((p->x_p - 20) / 80)] == 1 ||
        mapValues[(int)floor((p->y_p - 20) / 80)][(int)floor((p->x_p + 20) / 80)] == 1 || mapValues[(int)floor((p->y_p + 20) / 80)][(int)floor((p->x_p + 20) / 80)] == 1)
    {
        p->x_p = old_x;
        p->y_p = old_y;
    }

}


void move_right(t_player *p)
{
    double old_x;
    double old_y;

    old_x = p->x_p;
    old_y = p->y_p;

    p->x_p = p->x_p + cos(-p->angle * (M_PI / 180) + (M_PI / 2)) * 4;
    p->y_p = p->y_p + sin(-p->angle * (M_PI / 180) + (M_PI / 2)) * 4;

    if (mapValues[(int)floor((p->y_p - 20) / 80)][(int)floor((p->x_p) / 80)] == 1 || mapValues[(int)floor((p->y_p) / 80)][(int)floor((p->x_p + 20) / 80)] == 1 
        || mapValues[(int)floor((p->y_p) / 80)][(int)floor((p->x_p - 20) / 80)] == 1 || mapValues[(int)floor((p->y_p + 20) / 80)][(int)floor((p->x_p) / 80)] == 1
        || mapValues[(int)floor((p->y_p + 20) / 80)][(int)floor((p->x_p - 20) / 80)] == 1 || mapValues[(int)floor((p->y_p - 20) / 80)][(int)floor((p->x_p - 20) / 80)] == 1 ||
        mapValues[(int)floor((p->y_p - 20) / 80)][(int)floor((p->x_p + 20) / 80)] == 1 || mapValues[(int)floor((p->y_p + 20) / 80)][(int)floor((p->x_p + 20) / 80)] == 1)
    {
        p->x_p = old_x;
        p->y_p = old_y;
    }

}

void move_left(t_player *p)
{
    double old_x;
    double old_y;

    old_x = p->x_p;
    old_y = p->y_p;

    p->x_p = p->x_p + cos(-p->angle * (M_PI / 180) - (M_PI / 2)) * 4;
    p->y_p = p->y_p + sin(-p->angle * (M_PI / 180) - (M_PI / 2)) * 4;

    if (mapValues[(int)floor((p->y_p - 20) / 80)][(int)floor((p->x_p) / 80)] == 1 || mapValues[(int)floor((p->y_p) / 80)][(int)floor((p->x_p + 20) / 80)] == 1 
        || mapValues[(int)floor((p->y_p) / 80)][(int)floor((p->x_p - 20) / 80)] == 1 || mapValues[(int)floor((p->y_p + 20) / 80)][(int)floor((p->x_p) / 80)] == 1
        || mapValues[(int)floor((p->y_p + 20) / 80)][(int)floor((p->x_p - 20) / 80)] == 1 || mapValues[(int)floor((p->y_p - 20) / 80)][(int)floor((p->x_p - 20) / 80)] == 1 ||
        mapValues[(int)floor((p->y_p - 20) / 80)][(int)floor((p->x_p + 20) / 80)] == 1 || mapValues[(int)floor((p->y_p + 20) / 80)][(int)floor((p->x_p + 20) / 80)] == 1)
    {
        p->x_p = old_x;
        p->y_p = old_y;
    }
}
