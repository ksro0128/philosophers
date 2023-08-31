CC = cc
CFLAGS = -Wall -Werror -Wextra
OBJS = main.o init.o ft_atol.o utils.o pthread_start.o philo_cycle.o eat_sleep_think.o
NAME = philo

all : $(NAME)

$(NAME) : $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

%.o : %.c
	$(CC) $(CFLAGS) $^ -c

clean :
	rm -rf $(OBJS)

fclean : clean
	rm -rf $(NAME)

re :
	make fclean
	make all
	
.PHONY : re clean fclean all