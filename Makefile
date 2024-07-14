##
## EPITECH PROJECT, 2024
## Firejam
## File description:
## Makefile
##

CXX			=	g++
CXXFLAGS	+=	-std=c++2a -Wall -Wextra -Werror
CPPFLAGS	+=	-iquote $(INC_DIR)
LDFLAGS		=	-lsfml-graphics -lsfml-window -lsfml-system

SRC_DIR		=	./src
INC_DIR		=	./includes

MAIN		=	$(SRC_DIR)/Main.cpp				\

SRC			=	$(SRC_DIR)/Gem.cpp				\
				$(SRC_DIR)/Game.cpp				\
				$(SRC_DIR)/Menu.cpp				\
				$(SRC_DIR)/Player.cpp			\
				$(SRC_DIR)/Obstacle.cpp			\
				$(SRC_DIR)/Environment.cpp		\
				$(SRC_DIR)/LevelLoader.cpp		\

SRC_OBJ		=	$(SRC:.cpp=.o)					\
				$(MAIN:.cpp=.o)					\

BIN_NAME	=	./firejam

all:  $(BIN_NAME)


$(BIN_NAME): $(SRC_OBJ)
	$(CXX) -o $@ $^ $(CPPFLAGS) $(CXXFLAGS) $(LDFLAGS)

clean:
	@ $(RM) $(SRC_OBJ)

fclean: clean
	@ $(RM) $(BIN_NAME)

re: fclean all

.PHONY: all clean fclean re
