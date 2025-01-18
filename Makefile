TARGET = scop

SRC_DIR = src
INC_DIR = include
OBJ_DIR = obj

CC = c++
CPPFLAGS = -Wall -Wextra -I$(INC_DIR) -fsanitize=address
LIBS = -lglfw -lGLEW -lGL

SRCS = $(wildcard $(SRC_DIR)/*.cpp) $(wildcard $(SRC_DIR)/*/*.cpp)
OBJS = $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SRCS))

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CPPFLAGS) -o $@ $(OBJS) $(LIBS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@ mkdir -p $(dir $@)
	$(CC) $(CPPFLAGS) -c $< -o $@


clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -rf $(TARGET)

re: clean all

.PHONY: all clean fclean re