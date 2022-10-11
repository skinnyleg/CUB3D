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

OFILES = $(addprefix $(OBJ_DIR)/,$(CFILES:.c=.o))

OBJ_DIR = ./obj

SRC_DIR = ./src

CFLAGS = -Wall -Werror -Wextra

INC = includes/CUB3D.h

LFLAGS = -lmlx -framework OpenGL -framework AppKit

LIBFT = libft/libft.a

NAME = cub3D

all : $(NAME)

$(NAME) : $(OBJ_DIR) $(LIBFT) $(OFILES)
	@$(CC) $(LFLAGS) $(OFILES) $(LIBFT) -o $(NAME)
	@echo "done for cub3D"

$(OBJ_DIR) :
	@mkdir obj

$(LIBFT) :
	@make -C libft

$(OFILES) : $(OBJ_DIR)/%.o : $(SRC_DIR)/%.c $(INC)
	$(CC) -c $(CFLAGS) $< -o $@

clean :
	@rm -rf $(OBJ_DIR)
	@make clean -C libft

fclean : clean
	@rm -rf $(NAME)
	@make fclean -C libft

re : fclean all
