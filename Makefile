NAME = sync.exe
PATH_HEAD = ./src/
PATH_SRCS = ./src/
SRCS = $(addprefix $(PATH_SRCS), main.c)
OBJ = $(SRCS:.c=.o)
CC = gcc
FLAGS = 

.PHONY: clean, all, re

all: $(NAME)

$(NAME): $(SRCS)
	$(CC) -o $(NAME) $(FLAGS) $(SRCS) $(PATH_SRCS)sync.res -I $(PATH_HEAD) 
clean:
	rm -f $(NAME)
re: clean all