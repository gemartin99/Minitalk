#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gemartin <gemartin@student.42barc...>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/15 18:21:24 by gemartin          #+#    #+#              #
#    Updated: 2022/03/07 18:03:44 by gemartin         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME_SERVER = server
NAME_CLIENT = client

SRCS_CLIENT = client.c
SRCS_SERVER = server.c
SRCS_CLIENTBONUS = client_bonus.c
SRCS_SERVERBONUS = server_bonus.c
OBJS_CLIENT = ${SRCS_CLIENT:.c=.o}
OBJS_SERVER = ${SRCS_SERVER:.c=.o}
OBJS_CLIENTBONUS = ${SRCS_CLIENTBONUS:.c=.o}
OBJS_SERVERBONUS = ${SRCS_SERVERBONUS:.c=.o}
CC = gcc
RM = rm -f
CFLAGS = -Wall -Wextra -Werror -MMD

all:	${OBJS_SERVER} ${OBJS_CLIENT}
		${CC} ${CFLAGS} ${SRCS_SERVER} -o ${NAME_SERVER}
		${CC} ${CFLAGS} ${SRCS_CLIENT} -o ${NAME_CLIENT}

bonus:	${OBJS_SERVERBONUS} ${OBJS_CLIENTBONUS}
		${CC} ${CFLAGS} ${SRCS_SERVERBONUS} -o ${NAME_SERVER}
		${CC} ${CFLAGS} ${SRCS_CLIENTBONUS} -o ${NAME_CLIENT}

client: ${OBJS_CLIENT}
		${CC} ${CFLAGS} ${SRCS_CLIENT} -o ${NAME_CLIENT}

server: ${OBJS_SERVER}
		${CC} ${CFLAGS} ${SRCS_SERVER} -o ${NAME_SERVER}

clean:
			${RM} ${OBJS_CLIENT} ${OBJS_SERVER} ${OBJS_CLIENTBONUS} ${OBJS_SERVERBONUS}

fclean: clean
			${RM} ${NAME_CLIENT} ${NAME_SERVER}

re: fclean all

.PHONY: all client server clean fclean re bonus
