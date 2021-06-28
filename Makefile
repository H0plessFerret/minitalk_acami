# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: acami <acami@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/06/27 20:41:21 by acami             #+#    #+#              #
#    Updated: 2021/06/28 17:13:08 by acami            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= minitalk
SERVER_NAME	= ./srcs/../server
CLIENT_NAME	= ./srcs/../client


SRC_DIR		=	./srcs/
SERVER_SRC	= 	ft_itoa.c \
server.c
CLIENT_SRC	=	ft_atoi.c \
client.c
SERVER_SRCS	=	$(addprefix $(SRC_DIR), $(SERVER_SRC))
CLIENT_SRCS	=	$(addprefix $(SRC_DIR), $(CLIENT_SRC))

OBJ_DIR		=	./objs/
SERVER_OBJS	=	$(addprefix $(OBJ_DIR), $(SERVER_SRC:.c=.o))
CLIENT_OBJS	=	$(addprefix $(OBJ_DIR), $(CLIENT_SRC:.c=.o))

CC				=	gcc
CFLAGS			=	-Wall -Wextra -Werror
INCLUDES		=	-I ./headers/

# COLORS
RED 	= 	\033[0;31m
GREEN 	= 	\033[0;32m
BLUE	=	\033[0;34m
CYAN	=	\033[0;36m
RESET 	= 	\033[0m

$(NAME) :	 		$(SERVER_NAME)  $(CLIENT_NAME)

all : 				$(NAME)

$(SERVER_NAME) :	$(OBJ_DIR) $(SERVER_OBJS)
					@echo "$(NAME): $(GREEN) Creating $(SERVER_NAME) $(RESET)"
					$(CC) $(CFLAGS) $(INCLUDES) $(SERVER_OBJS) -o $(SERVER_NAME)

$(CLIENT_NAME) :	$(OBJ_DIR) $(CLIENT_OBJS)
					@echo "$(NAME): $(GREEN) Creating $(CLIENT_NAME) $(RESET)"
					$(CC) $(CFLAGS) $(INCLUDES) $(CLIENT_OBJS) -o $(CLIENT_NAME)


bonus:				all

include $(wildcard $(OBJ_DIR)*.d)

$(OBJ_DIR) :
					@mkdir -p $(OBJ_DIR)
					@echo "$(NAME): $(GREEN)$(OBJ_DIR) was created$(RESET)"

$(OBJ_DIR)%.o :		$(SRC_DIR)%.c
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

re :				fclean all

.PHONY : 			all clean fclean re bonus server client