# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lsun <lsun@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/27 14:37:25 by lsun              #+#    #+#              #
#    Updated: 2023/06/08 11:44:04 by lsun             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

SRC = main.c philo_utils.c parsing.c thread_op.c routine.c
OBJ = $(SRC:.c=.o)
FLAGS = -Wall -Wextra -Werror
DBUG = -g -fsanitize=thread

all: $(NAME)

$(NAME): $(OBJ)
	cc $(OBJ) -o $(NAME) $(FLAGS)

$(OBJ): %.o: %.c
	cc -c $< -o $@ $(FLAGS)
clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re

