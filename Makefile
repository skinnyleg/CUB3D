CC = cc

CFILES = main.c\

OFILES = $(addprefix $(OBJ_DIR)/,$(CFILES:.c=.o))

OBJ_DIR = ./obj

SRC_DIR = ./src

CFLAGS = -Wall -Werror -Wextra

INC = includes/CUB3D.h

LBXFLAGS = -lmlx -framework OpenGL -framework AppKit

LIBFT = libft/libft.a

NAME = CUB3D

all : $(NAME)

$(NAME) : $(OBJ_DIR) $(LIBFT) $(OFILES)
	@$(CC) $(LIBFT) $(LBXFLAGS) $(OFILES) -o $(NAME)
	@echo "done for CUB3D"

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
