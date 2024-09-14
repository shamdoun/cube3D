#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "MLX42/include/MLX42/MLX42.h"


#define BLOCK_W 80
#define BLOCK_L 80
#define WHITE 0xFFFFFF
#define BLACK 0x0000000
#define PLAYER_C 0xFF000000
#define MIN(a,b) (((a)<(b))?(a):(b))
#define ABS(a) ((a < 0)?(-a):a)

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

typedef struct ray_v {
    int distance;
    double x;
    struct ray_v *next;
} t_ray;

typedef struct wall_v {
    int distance;
    int height;
    int wall_top;
    int wall_bot;
    struct wall_v *next;
} t_wall;


void move_right(t_player *p);
void move_left(t_player *p);
void move_down(t_player *p);
void move_up(t_player *p);
void key_func(void* param);
void terminate_game(t_map *m);
void update_map(t_map *m);
void rotate_angle(t_player *p, int value);
int get_rgba(int r, int g, int b, int a);
void draw_map(mlx_image_t *img);
void draw_block(mlx_image_t *img, int x, int y, int value);
void apply_dda_algorithm(t_map *m);
void draw_player(t_map *map);
void apply_dda_algorithm(t_map *m);
void draw_3d_walls(t_map *m);
void	ft_lstadd_back(t_ray **lst, t_ray *new);
t_ray	*ft_lstnew(int content, double x);