COMPILER=g++ -std=c++14
TARGET= gaze
OBJECTS= main.cpp image.cpp input.cpp
LINKER_FLAGS= -lSDL2 -lSDL2_image -lSDL2_ttf
DEBUG_FLAGS = -g -Wall -Wextra -Wpedantic

$(TARGET): $(OBJECTS)
	$(COMPILER) $(DEBUG_FLAGS) -o $@ $(OBJECTS)  $(LINKER_FLAGS)
