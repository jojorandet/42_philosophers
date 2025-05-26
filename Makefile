NAME			=			philo

CC				=			gcc
CFLAGS 			= 			-Wall -Werror -Wextra -g 

DIR_BIN			=			./bin
DIR_INCLUDES	=			./includes
DIR_SRC			=			./sources


OS = $(shell uname)
ifeq ($(OS), Darwin)
	CFLAGS += -fsanitize=address
endif 

SRCS			=			main.c \
							parsing.c \
							init_mutex.c \
							init_thread_data.c \
							utils.c \
							time_functions.c \
							launch_and_stop_routine.c \
							routine.c \
							exit.c

OBJS			= 			$(addprefix $(DIR_BIN)/src/, $(SRCS:.c=.o))

INCLUDE_FLAGS	=			-I$(DIR_INCLUDES)

all: $(NAME)

$(NAME): $(OBJS) | $(DIR_BIN)
	@$(CC) $(CFLAGS) $(OBJS) -o $@

$(DIR_BIN)/src/%.o: $(DIR_SRC)/%.c | $(DIR_BIN)/src
	@$(CC) $(CFLAGS) $(INCLUDE_FLAGS) -c $< -o $@

$(DIR_BIN):
	@mkdir -p $@

$(DIR_BIN)/src:
	@mkdir -p $@

clean:
	@rm -rf $(DIR_BIN)

fclean: clean
	@rm -rf $(NAME)

re: fclean all

PHONY: all clean
