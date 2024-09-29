# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: clagarci <clagarci@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/01 11:06:50 by clagarci          #+#    #+#              #
#    Updated: 2024/09/29 20:00:43 by clagarci         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex


LIBDIR = libft/
MY_SOURCES = src/pipex.c  src/errors.c src/execute_cmd.c #src/trying.c 

MY_OBJECTS = $(MY_SOURCES:.c=.o)

CC = gcc
CFLAGS += -Wall -Wextra -Werror -fsanitize=address
LIB_FLAGS =  -L./libft -lft -lm
GREEN = \033[0;32m
RED = \033[0;31m

all: $(NAME)

		
%.o : %.c
	$(CC) $(CFLAGS) -c -o $@ $< $(INCLUDES)
	
$(NAME): $(MY_OBJECTS)
		make -C $(LIBDIR)
		$(CC) $(CFLAGS) $(MY_OBJECTS) -o $(NAME) $(LIB_FLAGS)
		@echo "\n Compilation of $(NAME):  $(GREEN)SUCCESS!"

clean:
	rm -f $(MY_OBJECTS)
	@make clean -C libft

fclean: clean
	rm -f $(NAME)
	@make fclean -C libft

re: fclean all

.PHONY: all clean fclean re