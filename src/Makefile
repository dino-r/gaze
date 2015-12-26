COMPILER=g++ -std=c++14
TARGET= ../gaze
HEADERS= input.hpp SDL.hpp image.hpp
OBJECTS= main.o image.o input.o 
LINKER_FLAGS= -lSDL2 -lSDL2_image -lSDL2_ttf
DEBUG_FLAGS = -g -Wall -Wextra -Wpedantic

.PHONY: clean

$(TARGET): $(OBJECTS) $(HEADERS)
	$(COMPILER) $(DEBUG_FLAGS) -o $@ $(OBJECTS)  $(LINKER_FLAGS)

%.o: %.cpp 
	$(COMPILER) $(DEBUG_FLAGS) -c $<

main.o: main.cpp SDL.hpp image.hpp
image.o: image.cpp image.hpp

clean:
	rm -f *.o
