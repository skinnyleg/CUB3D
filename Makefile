CC = cc

CFILES = main.c\
		 gnl.c\
		 gnl_utils.c parse_upper.c parse_lower.c parse_up_lst.c parse_up_utils.c \

OFILES = $(addprefix $(OBJ_DIR)/,$(CFILES:.c=.o))

OBJ_DIR = ./obj

SRC_DIR = ./src

CFLAGS = -Wall -Werror -Wextra

INC = includes/CUB3D.h

LBXFLAGS = -lmlx -framework OpenGL -framework AppKit

LIBFT = libft/libft.a

NAME = cub3D

INCMLX = -I /usr/X11/include
INCLIB= /usr/X11/lib

LFLAGS = -L /usr/X11/lib -lX11 -lmlx -lXext


all : $(NAME)

$(NAME) : $(OBJ_DIR) $(LIBFT) $(OFILES)
	@$(CC) $(INCMLX) -g $(LBXFLAGS) $(LFLAGS) $(OFILES) $(LIBFT)  -o $(NAME)
	@echo "done for cub3D"

$(OBJ_DIR) :
	@mkdir obj

$(LIBFT) :
	@make -C libft

$(OFILES) : $(OBJ_DIR)/%.o : $(SRC_DIR)/%.c $(INC)
	$(CC) -c  $< -o $@

clean :
	@rm -rf $(OBJ_DIR)
	@make clean -C libft

fclean : clean
	@rm -rf $(NAME)
	@make fclean -C libft

re : fclean all
