PROJECTNAME = Simple_Student_Information_System
OUTPUT_DIR = build

SRC = $(wildcard src/*.cpp) $(wildcard src/windows/*.cpp) $(wildcard src/vault/*.cpp) $(wildcard src/appData/*.cpp) $(wildcard imgui/*.cpp)
INCLUDE_DIRS = -Iinclude/SDL2 -Iinclude/imgui
LIB_DIRS = -Llib

LIBS = -lSDL2
LIBS_WINDOWS = -lSDL2main -lSDL2

default:
	g++ $(SRC) -o $(OUTPUT_DIR)/$(PROJECTNAME) $(INCLUDE_DIRS) $(LIBS)

windows:
	g++ $(SRC) -o $(OUTPUT_DIR)/$(PROJECTNAME) $(INCLUDE_DIRS) $(LIB_DIRS) $(LIBS_WINDOWS)
