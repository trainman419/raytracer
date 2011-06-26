
LINK.o=$(LINK.cpp)

LDFLAGS=-lpng

HEADERS=spectrum.hpp ray.hpp object.hpp objects.hpp surface.hpp world.hpp png.hpp

all: main
	./main
	touch all

main: world.o objects.o png.o

main.o: $(HEADERS)
