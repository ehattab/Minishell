SRCS = parsing/main.c \
parsing/utils.c \
parsing/lexer.c \
parsing/tokenize.c \
parsing/utils_token.c \
parsing/free.c \
parsing/parser.c \
parsing/utils_parser.c \
exec/builtin.c\
exec/redirection.c\
exec/executable.c\
exec/executable1.c\
exec/builtin1.c\
parsing/error.c \
parsing/expander.c \
parsing/utils_expander.c \
exec/signaux.c\
exec/builtin2.c\
exec/redirection1.c\
parsing/error1.c\
parsing/expander1.c\
parsing/tokenize1.c\
exec/utilexec.c\
parsing/parser1.c\

OBJS = ${SRCS:.c=.o}
NAME = minishell
CC = gcc
CFLAGS = -Wall -Wextra -Werror -g3
RM = rm -rf
LIBFT = ./libft/libft.a
INCLUDES = -I/usr/include -Imlx -Iincludes

all: ${NAME}

${NAME}: ${OBJS} ${LIBFT}
	${CC} ${CFLAGS} ${OBJS} ${LIBFT} -lreadline -o ${NAME}

${LIBFT}:
	${MAKE} -C ./libft/

%.o: %.c
	${CC} ${CFLAGS} ${INCLUDES} -c $< -o $@

clean:
	${MAKE} clean -C ./libft/
	${RM} ${OBJS}

fclean: clean
	${MAKE} fclean -C ./libft/
	${RM} ${NAME}

re: fclean all

.PHONY: all clean fclean re
