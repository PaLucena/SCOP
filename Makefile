NAME = SCOP

CC = clang
FLAGS = -Wall -Wextra -Werror

SRC_PATH = src/
SRC = src/scop.c

OBJ_PATH = obj/

OBJ = $(patsubst $(SRC_PATH)/%.c,$(OBJ_PATH)/%.o,($(SRC)))