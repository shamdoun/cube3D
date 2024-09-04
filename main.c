#include "cube3D.h"
#include "mlx/mlx.h"


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
    map2d = {1, 1, 1, 1, 1,
     1, 0, 0, 0, 1,
     1, 0, 0, 0, 1,
     1, 1, 0, 0, 1,
     1, 1, 1, 1, 1};

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
    map2d->interface->mlx_ptr = mlx_init();
    if (!map2d->interface->mlx_ptr)
        exit (1);
    map2d->interface->win_ptr = mlx_new_window(map2d->interface->mlx_ptr, 800, 500, "overall_map");
    map2d->interface->new_img = mlx_new_image(map2d->interface->mlx_ptr, 800, 500);
}