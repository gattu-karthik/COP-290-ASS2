CXX = g++
CPPFLAGS = -w -std=c++11
LIBS = -lSDL2 -lSDL2_ttf -lSDL2_mixer -lSDL2_image


SOURCES=main.cpp maze.cpp texture.cpp player.cpp
OBJECTS=main.o maze.o texture.o player.o
EXECUTABLE=game

all: 
	$(CXX) -c $(CPPFLAGS) $(LIBS) $(SOURCES) 
	$(CXX) $(LIBS)  $(OBJECTS) -o $(EXECUTABLE)

clean:
	rm -f $(OBJECTS)
	rm -f $(EXECUTABLE)
