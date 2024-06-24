NAME = philo

SRCS = $(addprefix srcs/, main.c param.c error.c utils.c death.c time.c \
		philo.c output.c)

OBJS = $(SRCS:.c=.o)

CC = clang

INCLD = -I includes

RM = rm -f

CFLAGS = -Wall -Werror -Wextra -g

CFLAGS_FSANITIZE = -Wall -Werror -Wextra -fsanitize=thread -g -O1

LIBS = -lpthread

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LIBS)

F: $(OBJS)
	$(CC) $(CFLAGS_FSANITIZE) $(OBJS) -o $(NAME) $(LIBS)

$(OBJS): %.o: %.c
	$(CC) $(CFLAGS) $(INCLD) -o $@ -c $<

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
