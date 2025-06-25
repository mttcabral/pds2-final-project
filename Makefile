CC = g++
CFLAGS = -std=c++11 -Wall -g -I$(INCLUDE_DIR)

# Directories
INCLUDE_DIR = include
SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin
ASSETS_DIR = assets
TEST_DIR = tests

# for allegro library
PKG_CONFIG_LIBS = allegro-5 allegro_main-5 allegro_image-5 allegro_font-5 allegro_ttf-5 allegro_audio-5 allegro_acodec-5 allegro_primitives-5

CFLAGS += $(shell pkg-config --cflags $(PKG_CONFIG_LIBS))
LDFLAGS = $(shell pkg-config --libs $(PKG_CONFIG_LIBS))

# Tests
TEST_SOURCES = $(wildcard $(TEST_DIR)/*.cpp)
TEST_TARGET = $(BIN_DIR)/run_tests

# Sources
SOURCES = main polygon game_object hitbox entity game_object_handler cooldown animation passive base table leaderboard register
OBJECTS = $(addprefix $(OBJ_DIR)/, $(addsuffix .o, $(SOURCES)))

all: $(BIN_DIR)/main

$(BIN_DIR)/main: $(OBJECTS) | $(BIN_DIR) $(OBJ_DIR)
	$(CC) $(CFLAGS) $(OBJECTS) -o $@ $(LDFLAGS)
#	cp -r assets bin/

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

run:
	./bin/main

test: $(TEST_TARGET)
	./$(TEST_TARGET)

$(TEST_TARGET): $(OBJECTS) $(TEST_SOURCES)
	$(CC) $(CFLAGS) $(OBJECTS) $(TEST_SOURCES) -o $@ $(LDFLAGS)

clean:
	rm -rf $(OBJ_DIR)/*.o $(BIN_DIR)/main