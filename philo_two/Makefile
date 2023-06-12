# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cdelicia <cdelicia@42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/03/21 14:24:36 by cdelicia          #+#    #+#              #
#    Updated: 2023/06/12 08:37:47 by cdelicia         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY: all fclean clean re

CC = clang
NAME = philo_two
FLAGS = -Wall -Werror -Wextra
DFLAGS = -Wall -Werror -Wextra -g -fsanitize=address
SOURCES = utils.c main.c init.c threads.c atoi.c putstr.c check.c

O_FILES = $(SOURCES:.c=.o)

%.o: %.c $(HEADER)
	$(CC) $(FLAGS) -c $< -o $@

all: $(NAME)

$(NAME): $(O_FILES)
	$(CC) $(FLAGS) $(O_FILES) -o philo_two

clean:
	rm -f *.o

fclean: clean
	rm -f $(NAME)
	@rm -rf $(NAME).dSYM

re: fclean all
