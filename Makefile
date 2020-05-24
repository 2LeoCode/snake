# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lsuardi <lsuardi@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/05/24 16:50:01 by lsuardi           #+#    #+#              #
#    Updated: 2020/05/24 19:16:28 by lsuardi          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	snake
SRCDIR	=	src
OBJDIR	=	obj
INCDIR	=	inc
INC		=	snake.h
SRC		=	snake.c\
			snake_2.c\
			snake_3.c\
			snake_4.c\
			utils.c\
			utils_2.c
OBJ		=	$(SRC:.c=.o)
CFLAGS	=	-Wall -Wextra -Werror -I $(INCDIR)

all: $(NAME)
	@(echo 'Successfuly compiled $<')

$(NAME): $(addprefix ${OBJDIR}/, ${OBJ})
	@(echo 'Compiling [obj]'; gcc $^ -o $@ -lcurses)

$(OBJDIR):
	@(echo 'Creating [$@] directory'; mkdir $@)

$(OBJDIR)/%.o : $(SRCDIR)/%.c $(INCDIR)/$(INC) | $(OBJDIR)
	@(printf 'Compiling ('; gcc $(CFLAGS) -c $< -o $@; ls $(OBJDIR)/*.o | wc -l | tr -d ' \n'; printf ' / '; echo $(SRC) | wc -w | tr -d ' \n'; echo ')')

clean:
	@(rm -rf $(OBJDIR); echo 'Removed [$(OBJDIR)]')

fclean: clean
	@(rm -f $(NAME); echo 'Removed [$(NAME)]')

re: fclean all
