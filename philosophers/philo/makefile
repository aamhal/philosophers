Name = philo
CC = cc -g
Flags = -Wall -Wextra -Werror -fsanitize=address
SRC = main.c parsing.c philo_utiles.c philos.c
OBJ = $(SRC:.c=.o)

all : $(Name)


%.o : %.c philosophers.h
	$(CC) $(Flags) -c $< -o $@

$(Name) : $(OBJ)
	$(CC) $(Flags) $(OBJ) -o $(Name)

clean :
	@rm -rf *.o

fclean : clean
	@rm philo

re : fclean all