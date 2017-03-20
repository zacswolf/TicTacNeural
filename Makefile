CC=g++
CFLAGS=-c --std=c++11 -pedantic -Wall -Wextra -Wcast-align -Wcast-qual -Wctor-dtor-privacy -Wdisabled-optimization -Wformat=2 -Winit-self -Wmissing-declarations -Wmissing-include-dirs -Wold-style-cast -Woverloaded-virtual -Wredundant-decls -Wshadow -Wsign-conversion -Wsign-promo -Wstrict-overflow=5 -Wswitch-default -Wundef -Wno-unused
LDFLAGS=
SOURCES=src/main.cpp src/matrix.cpp src/csv.cpp src/network.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=tictac.out

all: $(SOURCES) $(EXECUTABLE)

clean:
	rm $(OBJECTS)
	    
$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@
	
.cpp.o:
	$(CC) $(CFLAGS) $< -o $@