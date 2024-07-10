##
## EPITECH PROJECT, 2024
## Firejam
## File description:
## Makefile
##

CXX			=	g++
CXXFLAGS	+=	-std=c++2a -Wall -Wextra -Werror
CPPFLAGS	+=	-iquote $(INC_DIR)


SRC_DIR		=	./src
INC_DIR		=	./includes

MAIN		=	$(SRC_DIR)/Main.cpp			\

SRC			=	$(SRC_DIR)/Firejam.cpp		\

SRC_OBJ		=	$(SRC:.cpp=.o)				\
				$(MAIN:.cpp=.o)				\

BIN_NAME	=	./firejam

all:  $(BIN_NAME)


$(BIN_NAME): $(SRC_OBJ)
	$(CXX) -o $@ $^ $(CPPFLAGS) $(CXXFLAGS)

clean:
	@ $(RM) $(SRC_OBJ)

fclean: clean
	@ $(RM) $(BIN_NAME)

re: fclean all

.PHONY: all clean fclean re
