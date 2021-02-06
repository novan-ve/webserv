# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: novan-ve <marvin@codam.nl>                   +#+                      #
#                                                    +#+                       #
#    Created: 2021/02/01 20:11:54 by novan-ve      #+#    #+#                  #
#    Updated: 2021/02/06 01:22:42 by tbruinem      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME = webserv

SRC_DIR = ./src/

HEADER = ./src/includes/Server.hpp
INCL := $(addprefix -I ,$(dir $(HEADER)))

SRC =	main.cpp \
		utilities.cpp \
		WebServer.cpp \
		Configuration.cpp \
		Parse.cpp \
		Location.cpp \
		URI.cpp \
		Client.cpp \
		Server.cpp
OBJ := $(SRC:%.cpp=./obj/%.o)
SRC := $(SRC:%=$(SRC_DIR)%)

FLAGS = -Wall -Werror -Wextra -pedantic -std=c++98

ifdef DEBUG
	FLAGS += -g -fsanitize=address
endif

CC = clang++

all: $(NAME)

obj/%.o: src/%.cpp
	mkdir -p $(@D)
	$(CC) $(FLAGS) $(INCL) -c $< -o $@

$(NAME): $(OBJ) $(HEADER)
	$(CC) $(FLAGS) $(INCL) $(OBJ) -o $(NAME)

clean:
	/bin/rm -f $(OBJ)

fclean: clean
	/bin/rm -f $(NAME)

re: fclean all
