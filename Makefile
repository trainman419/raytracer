
LINK.o=$(LINK.cpp)

CFLAGS=-g
CPPFLAGS=$(CFLAGS) $(shell pkg-config --cflags libpng)
LDFLAGS=$(shell pkg-config --libs libpng)

HEADERS=spectrum.hpp ray.hpp object.hpp objects.hpp surface.hpp world.hpp png.hpp optics.hpp approximation.hpp
OBJS=world.o object.o objects.o png.o spectrum.o source.o optics.o approximation.o

all: main spike model spectrum_test

main: $(OBJS)

spectrum_test: $(OBJS)

spike: approximation.o

model: optics.o approximation.o spectrum.o source.o

out.png: main
	./main
	open out.png

test.png: test.sh model
	./test.sh

spectrum.png: spectrum_test
	./spectrum_test
	open spectrum.png

clean:
	rm $(OBJS)
	rm main.o 
	rm main

main.o: $(HEADERS)
