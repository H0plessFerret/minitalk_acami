# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: acami <acami@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/06/27 20:41:21 by acami             #+#    #+#              #
#    Updated: 2021/06/27 21:06:16 by acami            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= minitalk
SERVER_NAME	= server
CLIENT_NAME	= client

SERVER_SRCS	= 	ft_itoa.c \
server.c
CLIENT_SRCS	=	ft_atoi.c \
client.c

OBJ_DIR		=	./objs/
SERVER_OBJS	=	$(addprefix $(OBJ_DIR), $(SERVER_SRCS:.c=.o))
CLIENT_OBJS	=	$(addprefix $(OBJ_DIR), $(CLIENT_SRCS:.c=.o))

CC				=	gcc
CFLAGS			=	-Wall -Wextra -Werror
INCLUDES		=	-I ./

# COLORS
RED 	= 	\033[0;31m
GREEN 	= 	\033[0;32m
BLUE	=	\033[0;34m
CYAN	=	\033[0;36m
RESET 	= 	\033[0m


$(NAME) :	 	server client

server :		$(OBJ_DIR) $(SERVER_OBJS)
				@echo "$(NAME): $(GREEN) Creating $(SERVER_NAME) $(RESET)"
				$(CC) $(CFLAGS) $(INCLUDES) $(SERVER_OBJS) -o $(SERVER_NAME)

client :		$(OBJ_DIR) $(CLIENT_OBJS)
				@echo "$(NAME): $(GREEN) Creating $(CLIENT_NAME) $(RESET)"
				$(CC) $(CFLAGS) $(INCLUDES) $(CLIENT_OBJS) -o $(CLIENT_NAME)

all : 			$(NAME)

bonus:			all

include $(wildcard $(OBJ_DIR)*.d)

$(OBJ_DIR) :
				@mkdir -p $(OBJ_DIR)
				@echo "$(NAME): $(GREEN)$(OBJ_DIR) was created$(RESET)"

$(OBJ_DIR)%.o :	%.c		
				$(CC) $(CFLAGS) -c $(INCLUDES) $< -o $@ -MMD

clean :
				@echo "$(NAME): $(BLUE) Deleting $(OBJ_DIR) $(RESET)"
				@rm -rf $(OBJ_DIR)
				
fclean :
				@echo "$(NAME): $(CYAN) Deleting $(OBJ_DIR) $(RESET)"
				@rm -rf $(OBJ_DIR)
				@echo "$(NAME): $(CYAN) Deleting $(SERVER_NAME) and $(CLIENT_NAME) $(RESET)"
				@rm -f $(SERVER_NAME)
				@rm -f $(CLIENT_NAME)	

re :			fclean all

.PHONY : 		all clean fclean re bonus server client