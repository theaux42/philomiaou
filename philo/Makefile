# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tbabou <tbabou@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/28 13:55:29 by tbabou            #+#    #+#              #
#    Updated: 2024/09/09 01:42:28 by tbabou           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
CC = cc
# CFLAGS := -Wall -Wextra -Werror -pthread
CFLAGS := -Wall -Wextra -pthread
LDFLAGS := -lpthread
INCLUDE_DIR = ./include
SOURCE_DIR = src
SOURCES = init.c philo.c monitor.c actions.c utils.c
SOURCES += philosophers.c
OBJECTS = $(addprefix $(SOURCE_DIR)/,$(SOURCES:.c=.o))

all: $(NAME)

$(NAME): $(OBJECTS)
	$(CC) -o $@ $(CFLAGS) $^ $(LIBS) $(LDFLAGS)

$(SOURCE_DIR)/%.o: %.c
	$(CC) -c $(CFLAGS) -I$(INCLUDE_DIR) $(LDFLAGS) $< -o $@

clean:
	rm -f $(OBJECTS)

fclean: clean
	rm -f $(NAME)

re: fclean all


.PHONY: all clean fclean re
