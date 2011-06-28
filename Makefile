
LINK.o=$(LINK.cpp)

LDFLAGS=-lpng

HEADERS=spectrum.hpp ray.hpp object.hpp objects.hpp surface.hpp world.hpp png.hpp

all: main out.png

main: world.o objects.o png.o spectrum.o source.o

out.png: main
	./main

main.o: $(HEADERS)
