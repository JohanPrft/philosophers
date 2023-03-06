# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jprofit <jprofit@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/30 10:15:50 by jprofit           #+#    #+#              #
#    Updated: 2023/01/30 16:02:43 by jprofit          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# ******** VARIABLES ******** #

# ---- Final Executable --- #

NAME			=	philo

# ---- Directories ---- #

DIR_OBJS		=	.bin/

DIR_SRCS		=	sources/

DIR_HEADERS		=	include/

# ---- Files ---- #

HEADERS_LIST	=	philo.h

SRCS_LIST		=	main.c		init.c			utils.c		philosophers.c	\
					parsing.c	philo_action.c	hitman.c

HEADERS			=	${HEADERS_LIST:%.h=${DIR_HEADERS}%.h}

OBJS			=	${SRCS_LIST:%.c=${DIR_OBJS}%.o}

# ---- Compilation ---- #

CFLAGS			=	-Wall -Wextra -Werror -pthread #-g

# ---- Commands ---- #

MKDIR			=	mkdir -p

RM				=	rm -rf

# ********* RULES ******** #

all				:	${NAME}

# ---- Variables Rules ---- #

${NAME}			:	${DIR_OBJS} ${OBJS} ${HEADERS}
					${CC} ${CFLAGS} -I ${DIR_HEADERS} ${OBJS} ${LIBRARY} -o ${NAME}

# ---- Compiled Rules ---- #

${OBJS}			:	${DIR_OBJS}%.o:	${DIR_SRCS}%.c ${HEADERS} Makefile
					${CC} ${CFLAGS} -I ${DIR_HEADERS} -c $< -o $@

${DIR_OBJS}		:
					${MKDIR} ${DIR_OBJS}

# ---- Usual Rules ---- #

run				:	all
					./${NAME}

clean			:
					${RM} ${OBJS}

fclean			:	clean
					${RM} ${NAME} ${DIR_OBJS}

re				:	fclean all

debug			:
					@echo ${OBJS} ${HEADERS}

.PHONY:	all run clean fclean re debug
