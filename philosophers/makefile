Name = philo
CC = cc
Flags = -Wall -Wextra -Werror
SRC = philo/main.c philo/parsing.c philo/philo_utiles.c philo/philos.c
OBJ = $(SRC:.c=.o)

all : $(Name)


%.o : %.c SRC/philosophers.h
	$(CC) $(Flags) -c $< -o $@

$(Name) : $(OBJ)
	$(CC) $(Flags) $(OBJ)

clean :
	@rm -rf philo/*.o

fclean : clean
	@rm a.out

re : fclean all