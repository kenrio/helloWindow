NAME		:= helloWindow

UNAME		:= $(shell uname -s)

CXX_C		:= c++
CXX_FLAGS	:= -Wall -Wextra -Werror

CC			:= gcc
C_FLAGS		:= -Wall -Wextra -Werror

SRC_DIR		:= src
BIN_DIR		:= bin
INC_DIR		:= include

SRC			:= \
			main.cpp \
			shader.cpp \

C_SRC		:= \
			glad.c \

BIN			:= \
			$(addprefix $(BIN_DIR)/, \
			$(SRC:.cpp=.o))

C_BIN		:= \
			$(addprefix $(BIN_DIR)/, \
			$(C_SRC:.c=.o))

ifeq ($(UNAME), Linux)
	GL_FLAGS	:= -lGL
	GLFW_FLAGS	:= -lglfw

	X11_FLAGS	:= -lX11

	LDFLAGS		:= $(GL_FLAGS) $(GLFW_FLAGS) $(X11_FLAGS) -lm
endif

ifeq ($(UNAME), Darwin)
	GL_FLAGS	:= -framework OpenGL
	GLFW_FLAGS	:= -lglfw

	LDFLAGS		:= $(GL_FLAGS) $(GLFW_FLAGS)
endif

INCLUDE		:= -I$(INC_DIR)

all: $(NAME)

run: all
	./$(NAME)

$(NAME): $(BIN) $(C_BIN)
	$(CXX_C) $(CXX_FLAGS) $(BIN) $(C_BIN) $(LDFLAGS) -o $@

$(BIN_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CXX_C) $(CXX_FLAGS) $(INCLUDE) -c $< -o $@

$(BIN_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(C_FLAGS) $(INCLUDE) -c $< -o $@

clean:
	$(RM) -rf $(BIN_DIR)

fclean: clean
	$(RM) $(NAME)

re: fclean all

glinfo:
ifeq ($(UNAME), Linux)
	@glxinfo | grep "OpenGL version"
	@glxinfo | grep "OpenGL renderer"
endif
ifeq ($(UNAME), Darwin)
	@system_profiler SPDisplaysDataType | grep -E "(OpenGL|Metal)"
endif


.PHONY: all run clean fclean re glinfo
