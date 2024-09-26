/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube3D.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamdoun <shamdoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 12:43:22 by shamdoun          #+#    #+#             */
/*   Updated: 2024/09/26 13:03:43 by shamdoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "MLX42/include/MLX42/MLX42.h"

#define BLOCK_W 64
#define BLOCK_L 64
#define WIDTH 21
#define HEIGHT 10
#define FOV 60

typedef struct mlx_v
{
	mlx_t		*mlx_ptr;
	mlx_image_t	*new_img;
	char		*title;
	int			width;
	int			height;
}	t_mlx;

typedef struct ray_calc_v
{
	double	x_inter;
	double	y_inter;
	double	ax;
	double	ay;
	double	angle;
	double	tan_angle;
	double	verif_y;
	double	verif_x;
}	t_ray_calc;

typedef struct line_vector
{
	int	line_length;
	int	x;
	int	y;
	int	x1;
	int	y1;
	int	dx;
	int	dy;
	int	sx;
	int	sy;
	int	err;
	int	e2;
}	t_line;

typedef struct player_v
{
	double	x_p;
	double	y_p;
	double	angle;
	int		rotation_speed;
}	t_player;

typedef struct map_v
{
	char			*type;
	struct mlx_v	*interface;
	int				**map_values;
	struct player_v	*player;
}	t_map;

typedef struct ray_v
{
	int				distance;
	int				hit_vertical;
	double			angle;
	double			x;
	double			bitmap_offset;
	struct ray_v	*next;
}	t_ray;

typedef struct bitmap_v
{
	mlx_texture_t	*texture;
	uint32_t		*arr;
	double			offset_x;
	double			offset_y;
	double			scaling_factor;
	uint32_t		color;
}	t_bitmap;

typedef struct wall_v
{
	float			distance;
	long			distance_to_projection;
	double			height;
	int				wall_height;
	int				wall_top;
	int				wall_bot;
	struct bitmap_v	*t;
	struct wall_v	*next;
}	t_wall;

typedef struct gradient_v
{
	uint8_t	start_r;
	uint8_t	start_g;
	uint8_t	start_b;
	uint8_t	end_r;
	uint8_t	end_g;
	uint8_t	end_b;
	float	t;
}	t_gradient;

void	move_right(t_player *p);
void	move_left(t_player *p);
void	move_down(t_player *p);
void	move_up(t_player *p);
void	key_func(void *param);
void	terminate_game(t_map *m);
void	update_map(t_map *m);
void	rotate_angle(t_player *p, int value);
int		get_rgba(int r, int g, int b, int a);
void	draw_map(mlx_image_t *img);
void	draw_block(mlx_image_t *img, int x, int y, int value);
void	apply_dda_algorithm(t_map *m);
void	draw_player(t_map *map);
void	draw_mini_map(t_map *m);
void	apply_dda_algorithm(t_map *m);
void	draw_3d_walls(t_map *m);
void	ft_lstadd_back(t_ray **lst, t_ray *new);
void	draw_3d_map(void);
t_ray	*ft_lstnew(double x);
void	draw_mini_map(t_map *m);
int		wall_contact(t_player *p);
int		get_map_value(t_player *p, int x, int y);
void	draw_circle(t_map *map, int x_center, int y_center, int radius);
void	init_player_instance(t_map *map3d);
void	my_put_mlx(t_map *map, int x, int y);
void	measure_all_rays(t_map *m, t_ray **rays);
int		convert_pixel_to_color(uint32_t color);
void	draw_sky(t_map *m, int x, t_wall *w);
void	draw_floor(t_wall *w, t_map *m, int x);
void	init_gradient(t_gradient *gradient);
void	draw_sky(t_map *m, int x, t_wall *w);
void	draw_floor(t_wall *w, t_map *m, int x);
void	apply_dda_algorithm(t_map *m);
int		mouvement_is_blocked(int map_y, int map_x, double angle);
int		ray_is_facing_left(double angle);
int		ray_is_facing_down(double angle);
long	calculate_magnitude(t_player *player, double x, double y);
void	draw_line(t_map *m, double angle, long h_distance);
void	init_vector_values(t_line *line, t_map *m,
			long h_distance, double angle);
void	initialise_params_for_hor_calc(t_ray_calc *hor, double angle);
void	init_first_hor_inter(t_ray_calc *hor, t_map *m,
			double *x_inter, double *y_inter);
long	find_horizontal_distance(t_map *m, t_ray **h, double angle);
long	find_vertical_distance(t_map *m, t_ray **v, double angle);
void	update_angle(double *angle);
long	find_min(long a, long b);
long	absolute_value(long a);