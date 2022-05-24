NAME = miniRT

ifeq ($(shell uname), Linux)
	MLX_DIR = ./srcs/mlx/mlx_x11/
	MLX = ./srcs/mlx/mlx_x11/libmlx_Linux.a
	LIB = -lXext -lX11 -lm -lbsd
else
	MLX_DIR = ./srcs/mlx_opengl/
	MLX = ./srcs/mlx_x11/libmlx.a
	LIB = -l mlx -framework OpenGL -framework AppKit -lm
	MLX_LNK	= -L $(MLX_DIR) 
endif

INC =	-I ./srcs\
		-I ./srcs/mlx/mlx_x11/\
		-I ./srcs/mlx/mlx_opengl/\
		-I ./srcs/parsing\
		-I ./srcs/math/\
		-I ./srcs/mlx_colors/\
		-I ./srcs/rendering/\
		-I ./srcs/libft/

SRCS =	main.c\
		math/polynomial.c\
		math/vectors.c\
		math/vectors2.c\
		math/vectors3.c\
		mlx_colors/color_color_ops.c\
		mlx_colors/color_scalar_ops.c\
		rendering/low_level.c\
		rendering/high_level.c

LIBFT = inc/libft/libft.a

CFLAGS = #-Wall -Werror -Wextra -g3 -MMD

OBJDIR = objs
SRCDIR = srcs

OBJS = $(addprefix ${OBJDIR}/,${SRCS:.c=.o})
DEPS = $(OBJS:%.o=%.d)

all : ${NAME}

mlx :
		@echo -n "Compiling minilibx"
		@make -s -C ${MLX_DIR} > /dev/null 2>&1
		@echo "\033[32m\t\t[OK]\033[0m"

libft :
		@echo -n "Compiling libft"
		@make -s -C srcs/libft
		@echo "\033[32m\t\t\t[OK]\033[0m"

$(NAME) : mlx libft ${OBJS}
		@echo -n  "Generating ${NAME}"
		@${CC} ${CFLAGS} ${OBJS} ${MLX} ${LIB} -o ${NAME} 
		@echo "\033[32m\t\t[OK]\033[0m"

bonus : $(NAME)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
		@mkdir -p ${@D}
		@${CC} ${CFLAGS} ${INC} -c $< -o $@
		
clean :	
		@echo -n "deleting mlx object files"
		@make clean -s -C ${MLX_DIR} > /dev/null
		@echo "\033[32m\t[OK]\033[0m"
		@echo -n "deleting libft object files"
		@make clean -s -C srcs/libft > /dev/null
		@echo "\033[32m\t[OK]\033[0m"
		@echo -n "deleting object files"
		@rm -rf ${OBJDIR} > /dev/null
		@echo "\033[32m\t\t[OK]\033[0m"

fclean : clean
		@rm -rf ${NAME} ${MLX} ${LIBFT}
		@echo "full clean\033[32m\t\t\t[OK]\033[0m"

re : fclean all

l.PHONY: all, clean, fclean, re, libft, test, bonus, mlx, testbonus
