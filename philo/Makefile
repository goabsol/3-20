# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: arhallab <arhallab@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/12/28 12:40:42 by arhallab          #+#    #+#              #
#    Updated: 2021/12/28 12:44:58 by arhallab         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

SRC = philosophers.c utils.c

OBJ = $(SRC:.c=.o)

all: ${NAME}

${NAME}: ${OBJ}
	gcc  -o $@ $^ -Wall -Wextra -Werror -fsanitize=address -g

%.o: %.c
	gcc -Wall -Wextra -Werror -c $?

clean:
	rm -rf ${OBJ}
	
fclean: clean
	rm -rf ${NAME}
re: fclean allMakefile

