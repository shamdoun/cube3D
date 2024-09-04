#include <stdlib.h>

typedef struct mlx_v {
    void *mlx_ptr;
    void *win_ptr;
    void *new_img;
    char *title;
    int  width;
    int height;
} t_mlx;

typedef struct player_v{
    int x_p;
    int y_p;
    double angle;
    int rotation_speed;
}   t_player;

typedef struct map_v{
    char *type;
    struct mlx_v *interface;
    int **map_values;
    struct player_v *player;
} t_map;
