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

BCFILES = main.c\
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
		utils2.c\
		draw_background.c\
		textures.c\
		mouse.c\
		minimap.c\

OFILES = $(addprefix $(OBJ_DIR)/,$(CFILES:.c=.o))

BOFILES = $(addprefix $(OBJ_DIRB)/,$(BCFILES:.c=.o))

OBJ_DIR = ./mandatory/obj

SRC_DIR = ./mandatory/src

OBJ_DIRB = ./bonus/obj

SRC_DIRB = ./bonus/src

CFLAGS = -Wall -Werror -Wextra

INC = ./mandatory/includes/CUB3D.h

INCB = ./bonus/includes/CUB3D.h

LFLAGS = -lmlx -framework OpenGL -framework AppKit


LIBFT = libft/libft.a

NAME = cub3D

NAME_B = cub3D_bonus

all : $(NAME)

$(NAME) : $(OBJ_DIR) $(LIBFT) $(OFILES)
	@$(CC) $(LFLAGS) $(OFILES) $(LIBFT) -o $(NAME)
	@echo "done for cub3D"

bonus : $(NAME_B)

$(NAME_B) : $(OBJ_DIRB) $(LIBFT) $(BOFILES)
	@$(CC) $(LFLAGS) $(BOFILES) $(LIBFT) -g -o $(NAME_B)
	@echo "done for cub3D bonus"

$(OBJ_DIR) :
	@mkdir $(OBJ_DIR)

$(OBJ_DIRB) :
	@mkdir $(OBJ_DIRB)

$(LIBFT) :
	@make -C libft

$(BOFILES) : $(OBJ_DIRB)/%.o : $(SRC_DIRB)/%.c $(INCB)
	@$(CC) -c $(CFLAGS) $< -o $@

$(OFILES) : $(OBJ_DIR)/%.o : $(SRC_DIR)/%.c $(INC)
	@$(CC) -c $(CFLAGS) $< -o $@

clean :
	@rm -rf $(OBJ_DIR) $(OBJ_DIRB)
	@make clean -C libft

fclean : clean
	@rm -rf $(NAME) $(NAME_B)
	@make fclean -C libft

re : fclean all

INCMLX=/usr/include

INCLIB=$(INCMLX)/../lib

HFLAGS = -L.. -lmlx -L$(INCLIB) -lXext -lX11 -lm -lbsd

debug : $(OBJ_DIRB) $(LIBFT) $(BOFILES)
	@$(CC) -fsanitize=address $(LFLAGS) $(BOFILES) $(LIBFT) -o $(NAME_B)
	@echo "done for cub3D (debug mode)"

pc : $(OBJ_DIR) $(LIBFT) $(OFILES)
	@$(CC) $(OFILES) $(HFLAGS) $(LIBFT) -o $(NAME)
	@echo "done for cub3D"

bonuspc : $(OBJ_DIRB) $(LIBFT) $(BOFILES)
	@$(CC) $(BOFILES) $(HFLAGS) $(LIBFT) -o $(NAME_B)
	@echo "done for cub3D BONUS"
