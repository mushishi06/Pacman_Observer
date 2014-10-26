NAME	=	pacman
CC		=	g++
CXXFLAGS	=	-W -Wall -Werror -g3
RM		=	rm -f
SRCS	=	main.cpp	\
			GameElement.cpp \
			ChangeManager.cpp \
			Bonus.cpp	\
			ACharacter.cpp	\
			Monster.cpp	\
			Player.cpp	\
			Cycle.cpp	\
			Map.cpp

OBJS	=	$(SRCS:.cpp=.o)

all		: $(NAME)

$(NAME)	: $(OBJS)
		$(CC) $(OBJS) -o $(NAME)

clean	:
		$(RM) $(NAME)

fclean	: clean
		$(RM) $(OBJS)

re		: fclean all