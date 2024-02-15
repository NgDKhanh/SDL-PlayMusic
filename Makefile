CC = g++
CPPFLAG = -Wall -g -std=c++17
SRC_DIR = src
INC_DIR = inc
OBJ_DIR = obj
BIN_DIR = bin
MAIN_DIR = main

SRC := $(wildcard $(SRC_DIR)/*.cpp)
OBJ := $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(filter-out $(MAIN_DIR)/main.cpp,$(SRC))) $(OBJ_DIR)/main.o
TARGET := $(BIN_DIR)/main

.PHONY: all
all: directories $(TARGET)

$(TARGET): $(OBJ)
	$(CC) -o $@ $? -lSDL2 -lSDL2_image -lSDL2_mixer -pthread

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp 
	$(CC) $(CPPFLAG) -c -o $@ $< -I$(INC_DIR)

$(OBJ_DIR)/main.o: $(MAIN_DIR)/main.cpp
	$(CC) $(CPPFLAG) -c -o $@ $< -I$(INC_DIR)

.PHONY: directories
directories:
	mkdir -p $(OBJ_DIR) $(BIN_DIR)

.PHONY: clean
clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)

.PHONY: run
run: all
	./$(TARGET)