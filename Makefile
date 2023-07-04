# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lsun <lsun@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/27 14:37:25 by lsun              #+#    #+#              #
#    Updated: 2023/07/04 18:45:35 by lsun             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

SRCS = parsing.c thread_op.c routine.c time.c utils.c
SRCSDEST = $(addprefix ./SRCS/, $(SRCS))
OBJ = $(SRC:.c=.o)
FLAGS = -Wall -Wextra -Werror
DBUG = -g -fsanitize=thread -static-libsan

all: $(NAME)

$(NAME): $(SRCSDEST) main.c includes/philo.h
	cc $(FLAGS) $(SRCSDEST) -o $(NAME) main.c

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re

