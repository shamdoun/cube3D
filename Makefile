cc = cc
C_FLAGS = -Werror -Wall -Wextra
NAME = cub3D

srcs = main.c
objs = ${srcs:.c=.o}


%.o : %.c cube3D.h
	${CC} ${C_FLAGS} -Imlx -c $< -o $@  

all : ${NAME}

${NAME}: ${objs}
	${CC} ${objs} -Lmlx -Lmlx -framework OpenGL -framework AppKit -o ${NAME}

clean:
	rm -fr ${objs}

fclean: clean
	rm -fr ${NAME}

re: fclean all