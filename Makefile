CC = cc

CFILES = main.c\
		 gnl/get_next_line.c\
		 gnl/get_next_line_utils.c\

OFILES = $(addprefix $(OBJ_DIR)/,$(CFILES:.c=.o))

OBJ_DIR = ./obj

SRC_DIR = ./src

CFLAGS = -Wall -Werror -Wextra

INC = includes/CUB3D.h

LBXFLAGS = -lmlx -framework OpenGL -framework AppKit

LIBFT = libft/libft.a

NAME = cub3D

INC=/usr/include

LFLAGS = -L.. -lmlx -L$(INCLIB) -lXext -lX11 -lm -lbsd

INCLIB=$(INC)/../lib

all : $(NAME)

$(NAME) : $(OBJ_DIR) $(LIBFT) $(OFILES)
	@$(CC) $(OFILES) $(LIBFT) $(LFLAGS) -o $(NAME)
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
