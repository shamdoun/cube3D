cc = cc
C_FLAGS = #-Werror -Wall -Wextra
MLX_LIB = MLX42/build/libmlx42.a
MLX_FLAGS = -framework Cocoa -framework OpenGL -framework IOKit
NAME = cub3D

srcs = main.c mouvements.c render.c hooks.c drawing_algorithms.c
objs = ${srcs:.c=.o}


%.o : %.c cube3D.h
	${CC} ${C_FLAGS} -Iinclude -c -g $< -o $@  

all : ${NAME}


${NAME}: ${objs}
	${CC} ${objs} ${MLX_FLAGS} ${MLX_LIB} -Iinclude -lglfw -L"/opt/homebrew/Cellar/glfw/3.4/lib/" -o ${NAME}

clean:
	rm -fr ${objs}

fclean: clean
	rm -fr ${NAME}

pre:
	cd MLX42 && cmake -B build && cmake --build build -j4

re: fclean all