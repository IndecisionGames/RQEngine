# Directories
S_DIR=src
R_DIR=res
L_DIR=lib/debug
B_ROOT=bin
B_DIR=bin/debug
LIBS_DIR=lib/third-party

# Files
S_FILES=*.cpp src/*.cpp src/common/*.cpp

# Output
EXEC=$(B_DIR)/RQEngine

# Build settings
CC=g++

# Win
COMPILER_FLAGS = -std=c++14 -g -Wall -m64
INCLUDE_FLAGS = -I include -I ${LIBS_DIR}/SDL2-w64/include -I ${LIBS_DIR}/glew-2.2.0/include -I ${LIBS_DIR}/glm/
LIBRARY_FLAGS = -L ${LIBS_DIR}/SDL2-w64/lib -L ${LIBS_DIR}/glew-2.2.0/lib/Release/x64
LINKER_FLAGS = -lmingw32 -lglew32 -lOpenGL32 -lglu32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf

# OSX
CFLAGS = -std=c++14 -g -Wall -I/usr/local/include/SDL2 -I/usr/local/include/GL -I/usr/local/include/glm -Iinclude
LDFLAGS:= -L/usr/local/lib
LDLIBS:= -framework OpenGL -lGLEW -lSDL2 -lSDL2_image -lSDL2_ttf 

# Build for windows by default
all:Build

Build:
	mkdir -p $(B_DIR)/$(R_DIR)
	yes|cp -ruv $(L_DIR)/* $(B_DIR)/.
	yes|cp -ruv $(R_DIR)/* $(B_DIR)/$(R_DIR)/.
	if $(CC) $(S_FILES) $(COMPILER_FLAGS) $(INCLUDE_FLAGS) $(LIBRARY_FLAGS) $(LINKER_FLAGS) -o $(EXEC); then echo -e "\nBUILD SUCCEEDED\n"; else echo -e "\nBUILD FAILED\n"; fi


run:Build
	$(EXEC)

osx-build:
	mkdir -p $(B_DIR)/$(R_DIR)
	rsync -auv $(R_DIR)/ $(B_DIR)/$(R_DIR)/
	if $(CC) $(S_FILES) $(CFLAGS) $(LDFLAGS) $(LDLIBS) -o $(EXEC); then echo "\nBUILD SUCCEEDED\n"; else echo "\nBUILD FAILED\n"; fi 

osx:osx-build
	$(EXEC)

osx-full:osx-prep osx

clean:
	rm -rf $(B_ROOT)