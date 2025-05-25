PROG	= pipex

SRCS 	= SRCS/pipex.c SRCS/utils.c
OBJS 	= ${SRCS:.c=.o}
MAIN	= SRCS/pipex.c

HEADER	= -Iincludes

CC 		= gcc
CFLAGS 	= -Wall -Wextra -Werror -g

.c.o:		%.o : %.c
					@gcc ${CFLAGS} ${HEADER} -c $< -o $(<:.c=.o)

all: 		${PROG}

${PROG}:	${OBJS}
					@echo "Compiling the Libft\n"
					@make re -C ./Libft
					@$(CC) ${OBJS} -LLibft -lft -o ${PROG}
					@echo '__________.__                      '
					@echo '\______   \__|_____   ____ ___  ___'
					@echo ' |     ___/  \____ \_/ __ \\  \/  /'
					@echo ' |    |   |  |  |_> >  ___/ >    < '
					@echo ' |____|   |__|   __/ \___  >__/\_ \'
					@echo '             |__|        \/      \/'
					@echo "                     Compiled and ready to run !\n"

clean:
					@make clean -C ./Libft
					@rm -f ${OBJS} ${OBJS_B}

fclean: 	clean
					@make fclean -C ./Libft
					@rm -f $(NAME)
					@rm -f ${PROG}
					@echo '__________.__                      '
					@echo '\______   \__|_____   ____ ___  ___'
					@echo ' |     ___/  \____ \_/ __ \\  \/  /'
					@echo ' |    |   |  |  |_> >  ___/ >    < '
					@echo ' |____|   |__|   __/ \___  >__/\_ \'
					@echo '             |__|        \/      \/'
					@echo "                     Everything is Clean, See you soon !\n"

re:			fclean all

.PHONY: all clean fclean re