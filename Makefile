##
## Makefile<lib> for zappy in /home/totote/PSU_2014_zappy/server/lib
## 
## Made by Emeline Gaulard
## Login   <totote@epitech.net>
## 
## Started on  Wed May 13 16:11:07 2015 Emeline Gaulard
## Last update Thu Jul 16 18:17:01 2015 Emeline Gaulard
##

RM	=	rm -f

NAME	=	libnetk.a

CFLAGS	=	-W -Wall -Wextra -Werror

SRC	=	network.c		\
		network_client.c	\
		network_server.c	\
		utils.c			\
		ringbuffer.c		\
		list.c			\
		add_list.c		\
		del_list.c		\
		handle_poll.c		\
		data.c

OBJ	=	$(SRC:.c=.o)

$(NAME)	:	$(OBJ)
	ar rc $(NAME) $(OBJ)
	ranlib $(NAME)

all:		$(NAME)

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
