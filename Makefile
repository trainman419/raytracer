
LINK.o=$(LINK.cpp)

CFLAGS=-O3
CPPFLAGS=$(CFLAGS)
LDFLAGS=-lpng

HEADERS=spectrum.hpp ray.hpp object.hpp objects.hpp surface.hpp world.hpp png.hpp
OBJS=world.o object.o objects.o png.o spectrum.o source.o

all: main out.png

main: $(OBJS)

out.png: main
	./main

clean:
	rm $(OBJS)
	rm main.o 
	rm main

main.o: $(HEADERS)
