# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hezzahir <hamza.ezzahiry@gmail.com>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/19 18:32:21 by hezzahir          #+#    #+#              #
#    Updated: 2020/01/06 00:12:05 by hezzahir         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = rtv1

SRC_PATH = srcs
SRC_NAME = main.c vector.c check_ac.c parsing.c sphere.c camera.c get_data.c

OBJ_PATH = objs
OBJ_NAME = $(SRC_NAME:.c=.o)

CC = clang
CFLAGS = -Wall -Werror -Wextra

CPPFLAGS = -I includes -I libft/

HEADER = includes/rtv1.h

LDFLAGS = -L libft
LDLIBS = -O2 -lft -lm -lmlx -framework OpenGL -framework AppKit

SRC = $(addprefix $(SRC_PATH)/,$(SRC_NAME))
OBJ = $(addprefix $(OBJ_PATH)/,$(OBJ_NAME))

all: $(NAME)

$(NAME): $(OBJ)
		@echo "															";
		@echo "    ██████╗ ████████╗██╗   ██╗ ██╗						";
		@echo "    ██╔══██╗╚══██╔══╝██║   ██║███║						";
		@echo "    ██████╔╝   ██║   ██║   ██║╚██║						";
		@echo "    ██╔══██╗   ██║   ╚██╗ ██╔╝ ██║						";
		@echo "    ██║  ██║   ██║    ╚████╔╝  ██║						";
		@echo "    ╚═╝  ╚═╝   ╚═╝     ╚═══╝   ╚═╝						";
		@echo "			Made by : \033[1;91mSpiderX && Tamentino\033[m	";
		@echo "															";
		@make -C libft
		@$(CC) $(LDFLAGS) $(LDLIBS) $^ -o $@
		@echo "Compilation of Rtv1:  \033[1;32mOK\033[m"

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c $(HEADER)
		@mkdir $(OBJ_PATH) 2> /dev/null || true
		@$(CC) $(CFLAGS) -c $< $(CPPFLAGS) -o $@

clean:
		@make -C libft clean
		@rm -f $(OBJ)
		@rmdir $(OBJ_PATH) 2> /dev/null || true
		@echo "Rtv1 : Removing Objs"

fclean: clean
		@make -C libft fclean
		@rm -f $(NAME)
		@echo "Rtv1 : Removing rtv1"

re: fclean all
