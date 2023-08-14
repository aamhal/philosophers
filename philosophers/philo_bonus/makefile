Name = philo_bonus
CC = cc
Flags = -Wall -Wextra -Werror 
SRC = main.c parsing.c philo_utils.c philo_utils2.c routine.c
OBJ = $(SRC:.c=.o)

all : $(Name)


%.o : %.c philosophers.h
	@$(CC) $(Flags) -c $< -o $@

$(Name) : $(OBJ)
	@$(CC) $(Flags) $(OBJ) -o $(Name)

clean :
	@rm -rf *.o

fclean : clean
	@rm -rf $(Name)

re : fclean all