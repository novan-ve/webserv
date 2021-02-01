# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: novan-ve <marvin@codam.nl>                   +#+                      #
#                                                    +#+                       #
#    Created: 2021/02/01 20:11:54 by novan-ve      #+#    #+#                  #
#    Updated: 2021/02/01 21:10:58 by novan-ve      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME = webserv

SRC_DIR = ./src/

HEADER = ./src/includes/Server.hpp

SRC = main.cpp \
        Server.cpp \
        utilities.cpp

SRC := $(SRC:%=$(SRC_DIR)%)

OBJ = $(SRCS:.c=.o)

FLAGS = -Wall -Werror -Wextra -pedantic -std=c++98

CC = clang++

all: $(NAME)

$(NAME): $(SRC) $(HEADER)
	$(CC) $(FLAGS) $(SRC) -o $(NAME)

clean:
	/bin/rm -f $(OBJ)

fclean: clean
	/bin/rm -f $(NAME)

re: fclean all
