# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kaisuzuk <kaisuzuk@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/06/29 16:00:23 by kaisuzuk          #+#    #+#              #
#    Updated: 2025/07/09 23:00:21 by kaisuzuk         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	pipex
CC		=	cc
FLAG	=	-Wall -Werror -Wextra
INC		=	-Iincludes

_SRCS	=	execute_pipeline_bonus.c\
			parse_bonus.c\
			redir_bonus.c\
			findcmd_bonus.c \
			cmdutils_bonus.c \
			cmdlst_bonus.c \
			make_cmd_bonus.c \
			dispose_cmd_bonus.c
			
SRCS	=	$(addprefix src/, $(_SRCS))
OBJS	=	$(SRCS:.c=.o)
MAIN	=	main_bonus.c

FT_NAME	=	libftprintf
FT_URL	=	https://github.com/kaisuzuk2/ft_dprintf.git
INC		+=	-I$(FT_NAME)/includes
INC		+= 	-I$(FT_NAME)/libft
# INC		+=	-L$(FT_NAME)
# INC		+=	-lftprintf

GNL_NAME	=	libgnl
GNL_URL		=	https://github.com/kaisuzuk2/42-get_next_line.git
# INC		+=	-I$(GNL_NAME)
# INC		+=	-lgnl
INC		+=	-I$(GNL_NAME)

MAKE	=	make -C
RM		=	rm -rf

all: $(NAME)

$(NAME): $(FT_NAME) $(GNL_NAME) $(OBJS) $(MAIN)
	$(MAKE) $(FT_NAME)
	$(MAKE) $(GNL_NAME)
	$(CC) -o $(NAME) $(FLAG) $(INC) $(MAIN) $(OBJS) -L$(FT_NAME) -lftprintf -L$(GNL_NAME) -lgnl
	

%.o: %.c
	$(CC) -c $(FLAG) $(INC) $< -o $@

clean: 
	$(RM) $(FT_NAME)
	$(RM) $(GNL_NAME)
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

$(FT_NAME):
	git clone $(FT_URL) $(FT_NAME)

$(GNL_NAME):
	git clone $(GNL_URL) $(GNL_NAME)

.PHONY: clean fclean re


