# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: novan-ve <marvin@codam.nl>                   +#+                      #
#                                                    +#+                       #
#    Created: 2021/02/01 20:11:54 by novan-ve      #+#    #+#                  #
#    Updated: 2021/02/08 14:06:34 by tbruinem      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME = webserv

SRC_DIR = ./src/

HEADER =	Server.hpp \
			Client.hpp \
			configuration/Configuration.hpp \
			configuration/Context.hpp \
			configuration/Location.hpp \
			configuration/Parse.hpp \
			EnumString.hpp \
			Message.hpp \
			Method.hpp \
			Properties.hpp \
			Request.hpp \
			Response.hpp \
			Server.hpp \
			URI.hpp \
			Utilities.hpp \
			WebServer.hpp

HEADER :=	$(addprefix ./src/includes/, $(HEADER))

INCL_FOLDERS = $(dir $(HEADER))
INCL_FOLDERS := $(sort $(INCL_FOLDERS))

INCL := $(addprefix -I ,$(INCL_FOLDERS))

SRC =	main.cpp \
		utilities.cpp \
		WebServer.cpp \
		configuration/Configuration.cpp \
		configuration/Parse.cpp \
		configuration/Location.cpp \
		configuration/Context.cpp \
		Properties.cpp \
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

obj/%.o: src/%.cpp $(HEADER)
	mkdir -p $(@D)
	$(CC) $(FLAGS) $(INCL) -c $< -o $@

$(NAME): $(OBJ) $(HEADER)
	$(CC) $(FLAGS) $(INCL) $(OBJ) -o $(NAME)

clean:
	/bin/rm -f $(OBJ)

fclean: clean
	/bin/rm -f $(NAME)

re: fclean all
