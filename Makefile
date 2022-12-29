#
## Makefile of the project C Timer
#

NAME 	=	c_timer

SRC	=	src/main.c	\
		src/init_screens.c	\
		src/utils.c

OBJ	=	$(SRC:.c=.o)

CC 	=	gcc

CFLAGS	=	-g -W -Wall -Wextra -I ./includes

all	:	$(NAME)

$(NAME)	:	$(OBJ)
		$(CC) -o $(NAME) $(OBJ) -lncurses

clean	:
		rm -f $(OBJ)

fclean	:	clean
		rm -f $(NAME)

re	:	fclean $(NAME)

prog	:	$(NAME) clean