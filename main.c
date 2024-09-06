#include "cube3D.h"

int mapValues[10][21] = {
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1},
    {1, 1, 1, 0, 1, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1},
    {1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
};



int get_rgba(int r, int g, int b, int a)
{
    return (r << 24 | g << 16 | b << 8 | a);
}

void draw_block(mlx_image_t *img, int x, int y, int value)
{
    uint32_t color;
    int i;
    int j;

    if (value == 1)
        color = get_rgba(0,0,0,200);
    else
        color = get_rgba(255,255,255,255);
    i = 0;
    while (i < BLOCK_W - 1)
    {
        j = 0;
        while(j < BLOCK_L - 1)
        {
            mlx_put_pixel(img, y + j, x + i, color);
            j++;
        }
        i++;
    }
}


void draw_map(mlx_image_t *img)
{
    //draw blocks
    int i = 0;
    int j;
    while (i < 10)
    {
        j = 0;
        while (j < 21)
        {
            draw_block(img, i * 80, j * 80, mapValues[i][j]);
            j++; 
        }
        i++;
    };
}

void draw_direction(t_map *map, int x, int y)
{
    int line_length = 90; // Length of the line
    int x1, y1;
    int dx, dy, sx, sy, err, e2;

    // Calculate the endpoint of the line based on the angle and length
    x1 = x + cos(map->player->angle * (M_PI / 180) ) * line_length;
    y1 = y + sin(map->player->angle * (M_PI / 180) ) * line_length;

    dx = abs(x1 - x);
    dy = abs(y1 - y);
    sx = (x < x1) ? 1 : -1;
    sy = (y < y1) ? 1 : -1;
    err = dx - dy;

    while (1) {
        mlx_put_pixel(map->interface->new_img, x, y, get_rgba(0, 0, 255, 255));
        if (x == x1 && y == y1) break;
        e2 = err * 2;
        if (e2 > -dy) {
            err -= dy;
            x += sx;
        }
        if (e2 < dx) {
            err += dx;
            y += sy;
        }
    }
}

void draw_player(t_map *map)
{
    int x_center = map->player->x_p;
    int y_center = map->player->y_p;
    int radius = 10; // The radius of the circle

    int x, y;
    for (int i = 0; i <= radius * 2; i++)
    {
        for (int j = 0; j <= radius * 2; j++)
        {
            // Calculate the distance from the center of the circle
            int dx = i - radius;
            int dy = j - radius;
            if (dx * dx + dy * dy <= radius * radius)
            {
                x = x_center + dx;
                y = y_center + dy;
                mlx_put_pixel(map->interface->new_img, x, y, get_rgba(0,0,255,255));
            }
        }
    }
    draw_direction(map, map->player->x_p, map->player->y_p);
}


void rotate_angle(t_player *p, int value)
{
    p->angle += value;
    if (p->angle >= 360)
        p->angle -= 360;
    else if (p->angle < 0)
        p->angle += 360; 
}


void move_up(t_player *p)
{
    double old_x;
    double old_y;

    old_x = p->x_p;
    old_y = p->y_p;

    p->x_p = p->x_p + cos(p->angle * (M_PI / 180)) * 2;
    p->y_p = p->y_p + sin(p->angle * (M_PI / 180)) * 2;
}

void move_down(t_player *p)
{
    double old_x;
    double old_y;

    old_x = p->x_p;
    old_y = p->y_p;

    p->x_p = p->x_p + cos(p->angle * (M_PI / 180)) * -2;
    p->y_p = p->y_p + sin(p->angle * (M_PI / 180)) * -2;
}


void move_right(t_player *p)
{
    double old_x;
    double old_y;

    old_x = p->x_p;
    old_y = p->y_p;

    p->x_p = p->x_p + cos(p->angle * (M_PI / 180) + (M_PI / 2)) * 2;
    p->y_p = p->y_p + sin(p->angle * (M_PI / 180) + (M_PI / 2)) * 2;
}

void move_left(t_player *p)
{
    double old_x;
    double old_y;

    old_x = p->x_p;
    old_y = p->y_p;

    p->x_p = p->x_p + cos(p->angle * (M_PI / 180) - (M_PI / 2)) * 2;
    p->y_p = p->y_p + sin(p->angle * (M_PI / 180) - (M_PI / 2)) * 2;

}

void translate_x(t_player *p, int value)
{
    double old_x;
    double old_y;

    old_x = p->x_p;
    old_y = p->y_p;


    p->x_p = p->x_p + cos(p->angle * (M_PI / 180) + M_PI / 2) * value * 10;
    p->y_p = p->x_p + sin(p->angle * (M_PI / 180) + M_PI / 2) * value * 10;
    
    // if ((value > 0 && mapValues[(int)floor((p->y_p + 20) / 80)][(int)floor((p->x_p + 20) / 80)] == 1) || (value > 0 && mapValues[(int)floor((p->y_p - 20) / 80)][(int)floor((p->x_p + 20) / 80)] == 1) 
    //     || (value < 0 && mapValues[(int)floor((p->y_p - 20) / 80)][(int)floor((p->x_p - 20) / 80)]) || (value < 0 && mapValues[(int)floor((p->y_p + 20) / 80)][(int)floor((p->x_p - 20) / 80)]))
    //     p->x_p = old_p;
}

void update_map(t_map *m)
{
    mlx_delete_image(m->interface->mlx_ptr, m->interface->new_img);
    m->interface->new_img = mlx_new_image(m->interface->mlx_ptr, 21 * 80, 80 * 10);
    draw_map(m->interface->new_img);
    draw_player(m);
    mlx_image_to_window(m->interface->mlx_ptr, m->interface->new_img, 0, 0);
}

void translate_y(t_player *p, int value)
{
    double old_p;

    old_p = p->y_p; 
    if (!p->angle)
        p->y_p = p->y_p + value * 10;
    else
        p->y_p = p->y_p + sin(p->angle * (M_PI / 180)) * value * 10;
    if ((value < 0 && mapValues[(int)floor((p->y_p - 20) / 80)][(int)floor((p->x_p - 20) / 80)] == 1) || (value > 0 && mapValues[(int)floor((p->y_p + 20) / 80)][(int)floor((p->x_p + 20) / 80)]))
        p->y_p = old_p;
}

void terminate_game(t_map *m)
{
    mlx_delete_image(m->interface->mlx_ptr, m->interface->new_img);
    mlx_close_window(m->interface->mlx_ptr);
    mlx_terminate(m->interface->mlx_ptr);
    exit(1);
}

void key_func(void* param)
{
    t_map *m;
    m = (t_map *)param;
    if (mlx_is_key_down(m->interface->mlx_ptr, MLX_KEY_RIGHT))
        rotate_angle(m->player, 2);
    if (mlx_is_key_down(m->interface->mlx_ptr, MLX_KEY_LEFT))
        rotate_angle(m->player, -2);
    if (mlx_is_key_down(m->interface->mlx_ptr, MLX_KEY_D))
        move_right(m->player);
    if (mlx_is_key_down(m->interface->mlx_ptr, MLX_KEY_A))
        move_left(m->player);
    if (mlx_is_key_down(m->interface->mlx_ptr, MLX_KEY_W))
        move_up(m->player);
    if (mlx_is_key_down(m->interface->mlx_ptr, MLX_KEY_S))
        move_down(m->player);
    if (mlx_is_key_down(m->interface->mlx_ptr, MLX_KEY_ESCAPE))
        terminate_game(m);
    update_map(m);
}


int main()
{
    //creating the 2D map
    t_map *map2d;
    
    //init map
    map2d = (t_map *)malloc(sizeof(t_map));
    if (!map2d)
        exit (1);
    map2d->type = "2d map";

    //init map's values
    // map2d->map_values = malloc(sizeof(int) * 50);
    // if (!map2d->map_values)
    //     exit (1);

     //init player
     map2d->player = malloc(sizeof(t_player));
     if (!map2d->player)
        exit (1);
    map2d->player->x_p = 5 * 80 + 40;
    map2d->player->y_p = 3 * 80 + 40;
    map2d->player->angle = 0;
    map2d->player->rotation_speed = 2;

    //init interface
    map2d->interface = malloc(sizeof(t_map));
    if (!map2d->interface)
        exit (1);
    map2d->interface->mlx_ptr = mlx_init(21 *80, 10 * 80, "overall_map", false);
    if (!map2d->interface->mlx_ptr)
        exit (1);
    
    // //draw blocks
    map2d->interface->new_img = mlx_new_image(map2d->interface->mlx_ptr, 21 * 80, 80 * 10);
    draw_map(map2d->interface->new_img);
    
    //draw player
    draw_player(map2d);
    mlx_image_to_window(map2d->interface->mlx_ptr, map2d->interface->new_img, 0, 0);

    //hooks
    mlx_loop_hook(map2d->interface->mlx_ptr, &key_func, map2d);
    
    //loop
    mlx_loop(map2d->interface->mlx_ptr);
    mlx_terminate(map2d->interface->mlx_ptr);
    return (1);
}