#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "MLX42/include/MLX42/MLX42.h"

#define BLOCK_W 80
#define BLOCK_L 80
#define WHITE 0xFFFFFF
#define BLACK 0x0000000
#define PLAYER_C 0xFF000000

typedef struct mlx_v {
    mlx_t *mlx_ptr;
    mlx_image_t *new_img;
    char *title;
    int  width;
    int height;
} t_mlx;

typedef struct player_v{
    double x_p;
    double y_p;
    double angle;
    int rotation_speed;
}   t_player;

typedef struct map_v{
    char *type;
    struct mlx_v *interface;
    int **map_values;
    struct player_v *player;
} t_map;
