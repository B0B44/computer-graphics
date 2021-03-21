CC=g++
CFLAGS=-c -Wall -Wextra -fmax-errors=2
LD=g++
LDFLAGS=-lstdc++ -lc
SOURCES=Parser.cpp Application.cpp Command.cpp Cube.cpp Sphere.cpp Split.cpp main.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=MeshEditor

all: $(SOURCES) $(EXECUTABLE)
	
$(EXECUTABLE): $(OBJECTS) 
	$(LD) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	-rm $(OBJECTS) $(EXECUTABLE)
