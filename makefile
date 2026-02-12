PROJECTNAME = Simple_Student_Information_System
OUTPUT_DIR = build

INCLUDE_DIRS = -ISDL2
LIB_DIRS = -Llib

LIBS = -lSDL2main -lSDL2

SRC = $(wildcard src/*.cpp) $(wildcard src/windows/*.cpp) $(wildcard src/vault/*.cpp) $(wildcard src/appData/*.cpp) $(wildcard imgui/*.cpp)

default:
	g++ $(SRC) -o $(OUTPUT_DIR)/$(PROJECTNAME) $(INCLUDE_DIRS) $(LIB_DIRS) $(LIBS)
