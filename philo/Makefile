# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ralopez- <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/27 12:35:10 by ralopez-          #+#    #+#              #
#    Updated: 2023/01/27 12:35:13 by ralopez-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #



NAME = philo
CC = gcc
CFLAGS = -Wall -Wextra -Werror

ifdef TERM
RED			:=	"\033[1;31m"
GREEN		:=	"\033[0;32m"
BGREEN		:=	"\033[1;32m"
BLUE		:=	"\033[0;34m"
YELLOW		:=	"\033[0;33m"
PURPLE		:=	"\033[0;35m"
CYAN		:=	"\033[0;36m"
GREY		:=	"\033[0;37m"
# When printed reset the color
COLRESET	:=	"\033[0m"
endif

SRC = ft_validations.c ft_error.c ft_atoi.c ft_init.c ft_print.c ft_philo.c ft_main.c

OBJ = $(SRC:.c=.o)


%.o: %.c
	@echo $(GREEN) Compiling file $< $(COLRESET)
	@$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJ)
	@echo $(BLUE) Done!!! $(COLRESET)
	@$(CC) $(CFLAGS) $(OBJ) $(MLX) -o $(NAME)

all : $(NAME)

re : fclean all

clean :
	@echo $(RED) clean $(COLRESET)
	@$(RM) $(OBJ)

fclean : clean
	@echo $(RED) fclean $(COLRESET)
	@$(RM) $(NAME)

.PHONY: all clean fclean re
