
LINK.o=$(LINK.cpp)

EADERS=spectrum.hpp ray.hpp object.hpp objects.hpp surface.hpp world.hpp

all: main

main: world.o objects.o

main.o: $(HEADERS)
