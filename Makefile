# Compiler
CC = g++

# Debugger
DEBUGGER = gdb

#Memory Tester(For segfaults)
MEM_TESTER = valgrind

# Directories
SOURCE_DIR = src
OBJ_DIR = obj
BIN_DIR = bin
LIB_DIR = lib
INC_DIR = headers

#Final Executable
FINALEXE = Tictactoe

# Filenames
SRC_FILES = $(wildcard $(SOURCE_DIR)/*.cpp)
OBJ_FILES = $(patsubst %,$(OBJ_DIR)/%, $(notdir $(SRC_FILES:.cpp=.o)))
HEAD_FILES = $(wildcard $(INC_DIR)/*.hpp)

# Linking Flags
LFLAGS = -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -lsfml-network

# Compiler Flags
CFLAGS = -g

# Default Target
all: $(BIN_DIR)/$(FINALEXE)


# Building Instructions
$(BIN_DIR)/$(FINALEXE): $(OBJ_FILES)
	@echo [+] Linking object files with corresponding libraries
	@$(CC) -o $@ $^ $(LFLAGS)

$(OBJ_DIR)/%.o: $(SOURCE_DIR)/%.cpp
	@echo [+] Compiling sources
	$(CC) -c $^ $(CFLAGS) -o $@ -I $(INC_DIR)

# Running flags
run: $(BIN_DIR)/$(FINALEXE)
	@echo [+] Executing binary
	@./$<

debug: $(BIN_DIR)/$(FINALEXE)
	@echo [+] Executing binary with debugger
	@$(DEBUGGER) $@

memtest: $(BIN_DIR)/$(FINALEXE)
	@echo [+] Executing binary with memory tester
	@$(MEM_TESTER) $@

clean:
	@echo [+] Cleaning the project
	@rm $(OBJ_FILES) $(BIN_DIR)/$(FINALEXE)