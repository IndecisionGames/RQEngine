# Directories
S_DIR=src
R_DIR=res
L_DIR=lib/debug
B_DIR=bin/debug
LIBS_DIR=lib/third-party

# Files
S_FILES=$(S_DIR)/*.cpp

# Output
EXEC=$(B_DIR)/RQEngine

# Build settings
CC=g++

COMPILER_FLAGS = -std=c++14 -g -Wall -m64
INCLUDE_FLAGS = -I include -I ${LIBS_DIR}/SDL2-w64/include -I ${LIBS_DIR}/glew-2.2.0/include -I ${LIBS_DIR}/glm/
LIBRARY_FLAGS = -L ${LIBS_DIR}/SDL2-w64/lib -L ${LIBS_DIR}/glew-2.2.0/lib/Release/x64
LINKER_FLAGS = -lmingw32 -lglew32 -lOpenGL32 -lglu32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf

all:Build

Build:
	mkdir -p $(B_DIR)/$(R_DIR)
	yes|cp -ruv $(L_DIR)/* $(B_DIR)/.
	yes|cp -ruv $(R_DIR)/* $(B_DIR)/$(R_DIR)/.
	$(CC) main.cpp $(S_FILES) $(COMPILER_FLAGS) $(INCLUDE_FLAGS) $(LIBRARY_FLAGS) $(LINKER_FLAGS) -o $(EXEC) 

run:Build
	$(EXEC)

clean:
	rm -rf $(B_DIR)/*