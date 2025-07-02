# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kaisuzuk <kaisuzuk@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/06/29 16:00:23 by kaisuzuk          #+#    #+#              #
#    Updated: 2025/07/02 13:12:35 by kaisuzuk         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	pipex
CC		=	cc
FLAG	=	-Wall -Werror -Wextra
INC		=	-Iincludes

_SRCS	=	execute_pipeline_bonus.c\
			parse_bonus.c\
			redir_bonus.c\
			utils_bonus.c 
			
SRCS	=	$(addprefix src/, $(_SRCS))
OBJS	=	$(SRCS:.c=.o)
MAIN	=	main_bonus.c
INC		+=	-I$(FT_NAME)/includes
INC		+= -I$(FT_NAME)/libft

FT_NAME	=	libftprintf
FT_URL	=	https://github.com/kaisuzuk2/42-printf.git


MAKE	=	make -C
RM		=	rm -rf

all: $(NAME)

$(NAME): $(FT_NAME) $(OBJS) $(MAIN)
	$(MAKE) $(FT_NAME)
	$(CC) -o $(NAME) $(FLAG) $(INC) $(MAIN) $(OBJS) -L$(FT_NAME) -lftprintf
	

%.o: %.c
	$(CC) -c $(FLAG) $(INC) $< -o $@

clean: 
	$(RM) $(FT_NAME)
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

$(FT_NAME):
	git clone $(FT_URL) $(FT_NAME)

.PHONY: clean fclean 


