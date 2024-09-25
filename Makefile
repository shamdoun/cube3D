cc = cc
C_FLAGS = #-Werror -Wall -Wextra
MLX_LIB = MLX42/build/libmlx42.a
MLX_FLAGS = -framework Cocoa -framework OpenGL -framework IOKit
NAME = cub3D

srcs = main.c player/mouvements.c player/player.c render/render.c render/hooks.c map/map.c map/miniMap.c \
 libft/ft_lstadd_back.c libft/ft_lstnew.c raycasting/drawing_algorithms.c render/walls.c render/rays.c \
raycasting/horizontal_calc.c render/line.c raycasting/vertical_calc.c
objs = ${srcs:.c=.o}


%.o : %.c cube3D.h
	${CC} ${C_FLAGS} -Iinclude -c $< -o $@  

all : ${NAME}


${NAME}: ${objs}
	${CC} ${objs} ${MLX_FLAGS} ${MLX_LIB} -Iinclude -lglfw -L"/Users/shamdoun/.brew/opt/glfw/lib/" -fsanitize=address -o ${NAME}

clean:
	rm -fr ${objs}

fclean: clean
	rm -fr ${NAME}

pre:
	git clone https://github.com/codam-coding-college/MLX42.git
	cd MLX42 && cmake -B build && cmake --build build -j4

re: fclean all