# CC = g++
# SOURCE_DIR = src
# OBJ_DIR = obj
# BIN_DIR = bin
# LIB_DIR = lib
# INC_DIR = headers

# SRC_FILES = $(wildcard $(SOURCE_DIR)/*.cpp)
# OBJ_FILES = $(patsubst %,$(OBJ_DIR)/%, $(notdir $(SRC_FILES:.cpp=.o)))
# HEAD_FILES = $(wildcard $(INC_DIR)/*.hpp)

# FINALEXE = ttt

# LFLAGS = -lsfml-graphics -lsfml-window -lsfml-system
# CFLAGS = -Wall -g

# all: $(BIN_DIR)/$(FINALEXE)

# $(BIN_DIR)/$(FINALEXE): $(OBJ_FILES)
# 	$(CC) -o $@ $^ $(LFLAGS)

# $(OBJ_DIR)/%.o: $(SOURCE_DIR)/%.cpp $(HEAD_FILES)
# 	$(CC) -c $^ $(CFLAGS) -o $@

# .PHONY: run clean

# run:
# 	./$(BIN_DIR)/$(FINALEXE)

# clean:
# 	rm -rf $(OBJ_FILES) $(@) $(INC_DIR)/*.gch

SOURCE_DIR = src
OBJ_DIR = obj
BIN_DIR = bin
LIB_DIR = lib
COMPILER = g++

SRC_FILES = $(SOURCE_DIR)/*.cpp

FINALEXE = ttt

FLAGS = -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -lpthread -lsfml-network

CFLAGS = -g

build:
	$(COMPILER) $(CFLAGS) $(SRC_FILES) -o $(BIN_DIR)/$(FINALEXE) $(FLAGS)

run:
	./$(BIN_DIR)/$(FINALEXE) 