#include "cube3D.h"

int mapValues[10][21] = {
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1},
    {1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
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
    int i = 0;
    int j;
    int x1;
    int y1;

    while (i < 30)
    {
        x1 = cos(map->player->angle * (M_PI / 180)) * i;
        j = 0;
        while (j < 30)
        {
            y1 = sin(map->player->angle * (M_PI / 180)) * j;
            mlx_put_pixel(map->interface->new_img, x1 + x, y + y1, get_rgba(0,0,255,255));
            j++;
        }
        i++;
    }
}

void draw_player(t_map *map)
{
    int x_center = map->player->x_p * 80 + 40;
    int y_center = map->player->y_p * 80 + 40;
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
    draw_direction(map, map->player->x_p * 80 + 40, map->player->y_p * 80 + 40);
}


void rotate_angle(t_player *p, int value)
{
    p->angle += value;
    if (p->angle >= 360)
        p->angle -= 360;
    else if (p->angle < 0)
        p->angle += 360; 
}

void translate_x(t_player *p, int value)
{
    p->x_p = p->x_p + cos(p->angle * (M_PI / 180)) * value;
    p->x_p = p->x_p + sin(p->angle * (M_PI / 180)) * value;
}

void update_map(t_map *m)
{
    // mlx_delete_image(m->interface, m->interface->new_img);
    draw_map(m->interface->new_img);
    draw_player(m);
    draw_direction(m,m->player->x_p * 80 + 40, m->player->y_p * 80 + 40);
    mlx_image_to_window(m->interface->mlx_ptr, m->interface->new_img, 0, 0);
}

void key_func(mlx_key_data_t keydata, void* param)
{
    t_map *m;

    m = (t_map *)param;
    if (keydata.key == MLX_KEY_RIGHT)
        rotate_angle(m->player, 2);
    else if (keydata.key == MLX_KEY_LEFT)
        rotate_angle(m->player, -2);
    else if (keydata.key == MLX_KEY_UP)
        translate_x(m->player, 1);
    else if (keydata.key == MLX_KEY_DOWN)
        translate_x(m->player, -1);
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
    map2d->map_values = malloc(sizeof(int) * 50);
    if (!map2d->map_values)
        exit (1);

     //init player
     map2d->player = malloc(sizeof(t_player));
     if (!map2d->player)
        exit (1);
    map2d->player->x_p = 2;
    map2d->player->y_p = 3;
    map2d->player->angle = 0;
    map2d->player->rotation_speed = 26;

    //init interface
    map2d->interface = malloc(sizeof(t_map));
    if (!map2d->interface)
        exit (1);
    map2d->interface->mlx_ptr = mlx_init(21 *80, 10 * 80, "overall_map", false);
    if (!map2d->interface->mlx_ptr)
        exit (1);
    map2d->interface->new_img = mlx_new_image(map2d->interface->mlx_ptr, 21 * 80, 80 * 10);
    //draw blocks
    int i = 0;
    int j;
    while (i < 10)
    {
        j = 0;
        while (j < 21)
        {
            draw_block(map2d->interface->new_img, i * 80, j * 80, mapValues[i][j]);
            j++; 
        }
        i++;
    };

    //draw player
    map2d->player->x_p = 5;
    map2d->player->x_p = 3;
    draw_player(map2d);
    mlx_image_to_window(map2d->interface->mlx_ptr, map2d->interface->new_img, 0, 0);

    //hooks
    mlx_key_hook(map2d->interface->mlx_ptr, &key_func, map2d);
    //loop
    mlx_loop(map2d->interface->mlx_ptr);
    return (1);
}