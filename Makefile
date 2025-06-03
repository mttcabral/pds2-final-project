CC = g++
CFLAGS = -std=c++11 -Wall -I$(INCLUDE_DIR)

# Directories
INCLUDE_DIR = include
SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin

# Sources
SOURCES = main PLACE_HOLDER_1 #PLACE_HOLDER_2 PLACE_HOLDER_3 PLACE_HOLDER_4 PLACE_HOLDER_5 PLACE_HOLDER_6 PLACE_HOLDER_7 PLACE_HOLDER_8 PLACE_HOLDER_9
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