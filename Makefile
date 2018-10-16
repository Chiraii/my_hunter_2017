##
## EPITECH PROJECT, 2017
## Makefile
## File description:
## it's a file that makes, as usual.
##

SRC 	= 	my_hunter.c	\

NAME	=	my_hunter

all:	$(NAME)

$(NAME):
	gcc -o $(NAME) $(SRC) -lc_graph_prog

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all
