#include "cube3D.h"

int mapValues[10][21] = {
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1},
    {1, 1, 1, 0, 1, 1, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1},
    {1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
};

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
    // draw_player(map2d);
	apply_dda_algorithm(map2d);
    mlx_image_to_window(map2d->interface->mlx_ptr, map2d->interface->new_img, 0, 0);

    //hooks
    // mlx_loop_hook(map2d->interface->mlx_ptr, &key_func, map2d);
    
    //loop
    mlx_loop(map2d->interface->mlx_ptr);
    mlx_terminate(map2d->interface->mlx_ptr);
    return (1);
}