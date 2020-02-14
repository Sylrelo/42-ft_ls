# **************************************************************************** #
#                                                           LE - /             #
#                                                               /              #
#    Makefile                                         .::    .:/ .      .::    #
#                                                  +:+:+   +:    +:  +:+:+     #
#    By: slopez <slopez@student.le-101.fr>          +:+   +:    +:    +:+      #
#                                                  #+#   #+    #+    #+#       #
#    Created: 2018/11/25 11:57:33 by slopez       #+#   ##    ##    #+#        #
#    Updated: 2019/08/21 16:34:06 by slopez      ###    #+. /#+    ###.fr      #
#                                                          /                   #
#                                                         /                    #
# **************************************************************************** #

NAME	= ft_ls

SRCS	=	ft_ls.c errors.c ls_display.c ls_display_detailed.c sort.c \
			ls_read_dirs.c ls_read_files.c \
			params.c \
			ls_free.c \
			ls_display_lcols.c \
			ls_listutils.c \
			ls_details_perms.c \
			ls_tools.c \
			ls_display_detailed2.c

OBJ_DIR = ./.objs
SRC_DIR = ./srcs
INC_DIR = ./includes

CFLAGS	:= -Wall -Wextra  -I$(INC_DIR)
OBJS	:= $(patsubst %.c,$(OBJ_DIR)/%.o,  $(SRCS))


all: $(NAME)

$(OBJ_DIR):
		mkdir -p $(OBJ_DIR)

$(NAME): $(OBJS)
		@make -C libft/
		@gcc ${CFLAGS} -L./libft -lft $^ -o ${NAME}

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.c $(INC_DIR)/ft_ls.h $(INC_DIR)/structs.h | $(OBJ_DIR)
		@gcc $(CFLAGS) -o $@ -c $<
		@echo "compiling : $<"

clean:
		@rm -rf $(OBJ_DIR)
		@cd libft/ && make clean

fclean : clean
		@rm -f $(NAME)
		@cd libft/ && make fclean

re:		fclean all
