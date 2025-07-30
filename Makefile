# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kaisuzuk <kaisuzuk@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/06/29 16:00:23 by kaisuzuk          #+#    #+#              #
#    Updated: 2025/07/30 13:42:17 by kaisuzuk         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	pipex
B_NAME	=	pipex_bonus
CC		=	cc
FLAG	=	-Wall -Werror -Wextra
INC		=	-Iincludes

DEBUG_SANITIZE	=	-g -fsanitize=address
	
_SRCS	=	execute_pipeline_bonus.c\
			execute_pipeline_utils_bonus.c\
			ft_mkstemp_bonus.c \
			command_split_bonus.c \
			command_split_utils_bonus.c \
			parse_utils_bonus.c\
			redir_bonus.c\
			findcmd_bonus.c \
			findcmd_utils_bonus.c\
			cmdutils_bonus.c \
			cmdlst_bonus.c \
			cmdlst_utils_bonus.c \
			make_cmd_bonus.c \
			make_cmd_utils_bonus.c \
			dispose_cmd_bonus.c \
			error_bonus.c 
_M_SRCS	=	parse.c
_B_SRCS	=	parse_bonus.c
			
M_SRCS	=	$(addprefix src/, $(_SRCS) $(_M_SRCS))
B_SRCS	=	$(addprefix src/, $(_SRCS) $(_B_SRCS))
M_OBJS	=	$(M_SRCS:.c=.o)
B_OBJS	=	$(B_SRCS:.c=.o)
MAIN	=	main.c
B_MAIN	=	main_bonus.c

FT_NAME	=	libftprintf
FT_URL	=	https://github.com/kaisuzuk2/ft_dprintf.git
INC		+=	-I$(FT_NAME)/includes
INC		+= 	-I$(FT_NAME)/libft

GNL_NAME	=	libgnl
GNL_URL		=	https://github.com/kaisuzuk2/42-get_next_line.git
INC		+=	-I$(GNL_NAME)

MAKE	=	make -C
RM		=	rm -rf

# all: $(NAME)

# $(NAME): $(FT_NAME) $(GNL_NAME) $(M_OBJS) $(MAIN)
# 	$(RM) $(NAME)
# 	$(MAKE) $(FT_NAME)
# 	$(MAKE) $(GNL_NAME)
# 	$(CC) -o $(NAME) $(FLAG) $(INC) $(MAIN) $(M_OBJS) -L$(FT_NAME) -lftprintf -L$(GNL_NAME) -lgnl

# bonus: $(B_NAME)

# $(B_NAME): $(FT_NAME) $(GNL_NAME) $(B_OBJS) $(B_MAIN)
# 	$(RM) $(NAME)
# 	$(RM) $(B_NAME)
# 	$(MAKE) $(FT_NAME)
# 	$(MAKE) $(GNL_NAME)
# 	$(CC) -o $(B_NAME) $(FLAG) $(INC) $(B_MAIN) $(B_OBJS) -L$(FT_NAME) -lftprintf -L$(GNL_NAME) -lgnl
# 	cp $(B_NAME) $(NAME)

ifeq ($(MAKECMDGOALS), bonus)
	OBJS = $(B_OBJS)
else
	OBJS = $(M_OBJS)
endif 

all: $(FT_NAME) $(GNL_NAME) $(NAME)

$(NAME): $(OBJS)
	$(MAKE) $(FT_NAME)
	$(MAKE) $(GNL_NAME)
	$(CC) -o $(NAME) $(FLAG) $(INC) $(MAIN) $(OBJS) -L$(FT_NAME) -lftprintf -L$(GNL_NAME) -lgnl

bonus: all

%.o: %.c
	$(CC) -c $(FLAG) -g $(INC) $< -o $@

clean: 
	$(RM) $(FT_NAME)
	$(RM) $(GNL_NAME)
	$(RM) $(M_OBJS)
	$(RM) $(B_OBJS)

fclean: clean
	$(RM) $(NAME)
	$(RM) $(B_NAME)

re: fclean all

$(FT_NAME):
	git clone $(FT_URL) $(FT_NAME)

$(GNL_NAME):
	git clone $(GNL_URL) $(GNL_NAME)

.PHONY: clean fclean re bonus


