# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lkarri <lkarri@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/08/22 16:04:01 by lkarri            #+#    #+#              #
#    Updated: 2021/10/26 13:09:23 by lkarri           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	philo

SRCS		=	sources/main.c \
				sources/parse_and_init.c \
				sources/simulation.c \
				sources/utils.c \

OBJS		=	${SRCS:.c=.o}

HEADER		=	includes

CC			=	gcc

CFLAGS		=	-Wall -Werror -Wextra

RM			=	rm -f

LMAGNETA	=	\033[1;35m

LRED		=	\033[1;31m

NORMAL		=	\033[0m

.c.o:
				@ ${CC} ${CFLAGS} -I ${HEADER} -c $< -o ${<:.c=.o}

all:			${NAME}

${NAME}:		${OBJS}
				@ ${CC} -pthread ${CFLAGS} -o ${NAME} ${OBJS}
				@echo "${LMAGNETA}${NAME} ready to start${NORMAL}"

clean:
				@ ${RM} ${OBJS}

fclean:			clean
				@ ${RM} ${NAME}
				@echo "${LRED}all was deleted${NORMAL}"

re:				fclean all

.PHONY: all clean fclean re