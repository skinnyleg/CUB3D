CC = cc

CFILES = main.c\
		gnl.c\
		gnl_utils.c\
		parse_upper.c\
		parse_up_lst.c\
		parse_up_utils.c \
		parse_lower.c\
		parse_lower_utils.c\
		fill_map.c\
		wall_parser.c\
		destroy_global.c\
		mlx_render.c\
		destroy_global2.c\
		keys.c\
		ray_calculate.c\
		raycaster.c\
		wall3D.c\
		utils.c\
		draw_background.c\
		textures.c\

OFILES = $(addprefix $(OBJ_DIR)/,$(CFILES:.c=.o))

OBJ_DIR = ./obj

SRC_DIR = ./src

CFLAGS = -Wall -Werror -Wextra

INC = includes/CUB3D.h

LFLAGS = -lmlx -framework OpenGL  -Ofast  -framework AppKit

INCMLX=/usr/include

INCLIB=$(INCMLX)/../lib

HFLAGS = -L.. -lmlx -L$(INCLIB) -lXext -lX11 -lm -lbsd

LIBFT = libft/libft.a

NAME = cub3D

all : $(NAME)

$(NAME) : $(OBJ_DIR) $(LIBFT) $(OFILES)
	@$(CC) $(LFLAGS) $(OFILES) $(LIBFT) -o $(NAME)
	@echo "done for cub3D"

debug : $(OBJ_DIR) $(LIBFT) $(OFILES)
	@$(CC) -fsanitize=address $(LFLAGS) $(OFILES) $(LIBFT) -o $(NAME)
	@echo "done for cub3D (debug mode)"

pc : $(OBJ_DIR) $(LIBFT) $(OFILES)
	@$(CC) $(OFILES) $(HFLAGS) $(LIBFT) -o $(NAME)
	@echo "done for cub3D"

$(OBJ_DIR) :
	@mkdir obj

$(LIBFT) :
	@make -C libft

$(OFILES) : $(OBJ_DIR)/%.o : $(SRC_DIR)/%.c $(INC)
	@$(CC) -c $(CFLAGS) $< -o $@

clean :
	@rm -rf $(OBJ_DIR)
	@make clean -C libft

fclean : clean
	@rm -rf $(NAME)
	@make fclean -C libft

re : fclean all
