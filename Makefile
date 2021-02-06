# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: novan-ve <marvin@codam.nl>                   +#+                      #
#                                                    +#+                       #
#    Created: 2021/02/01 20:11:54 by novan-ve      #+#    #+#                  #
#    Updated: 2021/02/06 19:18:15 by tbruinem      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME = webserv

SRC_DIR = ./src/

HEADER =	./src/includes/Server.hpp \
			./src/includes/Attribute.hpp \
			./src/includes/Client.hpp \
			./src/includes/Configuration.hpp \
			./src/includes/Context.hpp \
			./src/includes/EnumString.hpp \
			./src/includes/Location.hpp \
			./src/includes/Message.hpp \
			./src/includes/Method.hpp \
			./src/includes/Parse.hpp \
			./src/includes/Properties.hpp \
			./src/includes/Request.hpp \
			./src/includes/Response.hpp \
			./src/includes/Server.hpp \
			./src/includes/URI.hpp \
			./src/includes/Utilities.hpp \
			./src/includes/WebServer.hpp \
			
INCL := $(addprefix -I ,$(dir $(HEADER)))
INCL := $(sort $(INCL)) #removes duplicates

SRC =	main.cpp \
		utilities.cpp \
		WebServer.cpp \
		Configuration.cpp \
		Parse.cpp \
		Attribute.cpp \
		Location.cpp \
		Context.cpp \
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
