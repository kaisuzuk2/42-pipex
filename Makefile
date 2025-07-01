# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kaisuzuk <kaisuzuk@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/06/29 16:00:23 by kaisuzuk          #+#    #+#              #
#    Updated: 2025/07/01 13:56:30 by kaisuzuk         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	pipex
CC		=	cc
FLAG	=	-Wall -Werror -Wextra


SRCS	=	
INC		=	-I$(FT_NAME)/includes

FT_NAME	=	libftprintf
FT_URL	=	git@vogsphere-v2.42tokyo.jp:vogsphere/intra-uuid-0303fe47-4568-4e00-ad9b-75f1c67325a9-6537121-kaisuzuk


MAKE	=	make -C
RM		=	rm -rf

all: $(NAME)

$(NAME): $(FT_NAME) $(OBJS)
	$(MAKE) $(FT_NAME)
	$(CC) -o $(NAME) $(FLAG) $(OBJS) -L$(FT_NAME) -l$(FT_NAME)
	

%.o: %.c
	$(CC) -c $(FLAG) $(INC) $< -o $@


$(FT_NAME): 
	git clone $(FT_URL) $(FT_NAME)



