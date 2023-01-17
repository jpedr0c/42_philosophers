# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jocardos <jocardos@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/08 11:23:57 by jocardos          #+#    #+#              #
#    Updated: 2023/01/17 10:42:37 by jocardos         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SHELL			= /bin/bash

NAME				= philo
OBJ_DIR			= object/
CC					= gcc
CFLAGS			= -Wall -Werror -Wextra -g
RM					= rm -f

#Styles
SET_COLOR	= \033[0:39m
RED				= \033[0;31m
GREEN			= \033[0;32m
YELLOW		= \033[0;33m
BLUE			= \033[0;34m
MAGENTA		= \033[0;35m
CYAN			= \033[0;36m
GRAY			= \033[0;90m
L_RED			=	\033[0;91m
L_GREEN		=	\033[0;92m
L_YELLOW	=	\033[0;93m
L_BLUE		=	\033[0;94m
L_MAGENTA	=	\033[0;95m
L_CYAN		=	\033[0;96m
WHITE			= \033[0;97m
BG_GREEN	= \033[42;1;37m

#Sources
SRC_FILES			= utils error config routine main

SRC = $(addprefix $(SRC_DIR), $(addsuffix .c, $(SRC_FILES)))
OBJ = $(addprefix $(OBJ_DIR), $(addsuffix .o, $(SRC_FILES)))

OBJF		=	.cache_exists

start:
			@echo -e -n "$(YELLOW)[Dependencies]:$(SET_COLOR)"
			@echo -e -n "$(WHITE)[$(SET_COLOR)"
			@make all

all:	$(NAME)

$(NAME):	$(OBJ) $(OBJF)
			@echo -e -n "$(WHITE)]$(SET_COLOR)"
			@echo -e -n "$(L_GREEN) => 100% ✅$(SET_COLOR)\n"
			@echo -e -n "$(YELLOW)[PHILOSOPHERS]:$(SET_COLOR)"
			@$(CC) $(CFLAGS) $(OBJ) -o $(NAME)
			@echo -e "$(L_GREEN) => Success ✅$(SET_COLOR)"

$(OBJ_DIR)%.o: $(SRC_DIR)%.c $(OBJF)
			@echo -e -n "$(L_GREEN)✓$(SET_COLOR)"
			@$(CC) $(CFLAGS) $(HEADER) -c $< -o $@

$(OBJF):
			@mkdir -p $(OBJ_DIR)
			@touch $(OBJF)

clean:
			@$(RM) -r $(OBJ_DIR)
			@$(RM) $(OBJF)
			@echo -e -n "$(MAGENTA)[PHILOSOPHERS]:$(SET_COLOR)$(BLUE) Object files$(SET_COLOR)$(GREEN)  => Cleaned$(SET_COLOR)"
			@echo -e " 🗑️$(SET_COLOR)"

fclean:		clean
			@$(RM) $(NAME)
			@$(RM) project.log
			@echo -e -n "$(MAGENTA)[PHILOSOPHERS]:$(SET_COLOR)$(BLUE) Executable files$(GREEN)  => Cleaned$(SET_COLOR)"
			@echo -e " 🗑️$(SET_COLOR)"

re:		fclean all
			@echo -e "\n$(BG_GREEN) => Cleaned and rebuilt everything <= $(SET_COLOR)"

.PHONY:	all start clean fclean re

valgrind: all
	valgrind --leak-check=full --show-reachable=yes --show-leak-kinds=all --error-limit=no --gen-suppressions=all --track-origins=yes  --log-file=project.log \
	./philo 4 310 200 100
	./philo 1 200 200 200
	./philo 1 800 200 200
	./philo 2 800 200 200 7
	./philo 5 800 200 200 7
	./philo 5 800 200 200 7
	./philo 4 410 200 200 7
	./philo 4 310 200 200
	./philo 4 310 200 100
	./philo 4 500 200 2147483647
	./philo 4 2147483647 200 200 7
	./philo 4 200 210 200
	cat project.log