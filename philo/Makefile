# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: arhallab <arhallab@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/12/28 12:40:42 by arhallab          #+#    #+#              #
#    Updated: 2022/02/01 06:16:01 by arhallab         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

SRC = philosophers.c utils.c philo_tools.c\
	  routine.c

OBJ = $(SRC:.c=.o)

all: ${NAME}

${NAME}: ${OBJ}
	gcc  -o $@ $^ -Wall -Wextra -Werror -pthread

%.o: %.c
	gcc -Wall -Wextra -Werror -c $?

clean:
	rm -rf ${OBJ}
	
fclean: clean
	rm -rf ${NAME}
re: fclean all

