
LINK.o=$(LINK.cpp)

CFLAGS=-g
CPPFLAGS=$(CFLAGS)
LDFLAGS=-lpng

HEADERS=spectrum.hpp ray.hpp object.hpp objects.hpp surface.hpp world.hpp png.hpp optics.hpp
OBJS=world.o object.o objects.o png.o spectrum.o source.o optics.o

all: main out.png

main: $(OBJS)

out.png: main
	./main

clean:
	rm $(OBJS)
	rm main.o 
	rm main

main.o: $(HEADERS)
