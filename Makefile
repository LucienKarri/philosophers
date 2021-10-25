# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lkarri <lkarri@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/08/22 16:04:01 by lkarri            #+#    #+#              #
#    Updated: 2021/10/09 01:08:53 by lkarri           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	philo

SRCS	=	sources/main.c \
			sources/parse_and_init.c \
			sources/simulation.c \
			sources/utils.c \

OBJS	=	${SRCS:.c=.o}

HEADER	=	includes

CC		=	gcc

CFLAGS	=	-Wall -Werror -Wextra

RM		=	rm -f

.c.o:
			${CC} ${CFLAGS} -I ${HEADER} -c $< -o ${<:.c=.o}

all:		${NAME}

${NAME}:	${OBJS}
			${CC} -pthread ${CFLAGS} -o ${NAME} ${OBJS}

clean:
			${RM} ${OBJS}

fclean:		clean
			${RM} ${NAME}

re:			fclean all

.PHONY: all clean fclean re