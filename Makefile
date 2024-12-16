TARGET = scop

SRC_DIR = src
INC_DIR = include
OBJ_DIR = obj

CC = c++
CPPFLAGS = -Wall -Wextra -I$(INC_DIR)
LIBS = -lglfw -lGLEW -lGL

SRCS = $(wildcard $(SRC_DIR)/*.cpp)
OBJS = $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SRCS))

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CPPFLAGS) -o $@ $(OBJS) $(LIBS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	$(CC) $(CPPFLAGS) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -rf $(TARGET)

re: clean all

.PHONY: all clean fclean re