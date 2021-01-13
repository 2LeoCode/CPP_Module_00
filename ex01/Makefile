# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lsuardi <lsuardi@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/01/11 23:30:39 by lsuardi           #+#    #+#              #
#    Updated: 2021/01/14 00:06:50 by lsuardi          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME =		PhoneBook

SRC =		main.cpp\
			PhoneBook.cpp
OBJ =		$(SRC:.cpp=.o)

CFLAGS =	-Wall -Wextra -Werror

all: $(NAME)
	@echo '$(NAME) is up to date.'

$(NAME): $(OBJ)
	@(\
		echo '\nCompiling $@...';\
		clang++ $(CFLAGS) $^ -o $@\
	)

%.o: %.cpp
	@(\
		printf '\r\033[2KCompiling $<...';\
		clang++ $(CFLAGS) -c $< -o $@\
	)

clean:
	@(\
		rm -f $(OBJ);\
		echo 'Removed $(OBJ)'\
	)

fclean: clean
	@(\
		rm -f $(NAME);\
		echo 'Removed $(NAME)'\
	)

re: fclean all
