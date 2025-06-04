CC = g++
CFLAGS = -std=c++11 -Wall -I$(INCLUDE_DIR)

# Directories
INCLUDE_DIR = include
SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin

# Sources
# To track a new ".cpp" file in Makefile, write it next to the last entry in SOURCES
SOURCES = main
OBJECTS = $(addprefix $(OBJ_DIR)/, $(addsuffix .o, $(SOURCES)))

all: $(BIN_DIR)/main

$(BIN_DIR)/main: $(OBJECTS) | $(BIN_DIR) $(OBJ_DIR)
	$(CC) $(CFLAGS) $(OBJECTS) -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

clean:
	rm -rf $(OBJ_DIR)/*.o $(BIN_DIR)/main