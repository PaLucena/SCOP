TARGET = scop

SRC_DIR = src
INC_DIR = include
OBJ_DIR = obj

CC = gcc
CFLAGS = -Wall -Wextra -I$(INC_DIR)
LIBS = -lglfw -lGLEW -lGL

SRCS = $(wildcard $(SRC_DIR)/*.c)
OBJS = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS))

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS) $(LIBS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -rf $(TARGET)

.PHONY: clean clean-all