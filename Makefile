
LINK.o=$(LINK.cpp)

CFLAGS=-g
CPPFLAGS=$(CFLAGS)
LDFLAGS=-lpng

HEADERS=spectrum.hpp ray.hpp object.hpp objects.hpp surface.hpp world.hpp png.hpp optics.hpp approximation.hpp
OBJS=world.o object.o objects.o png.o spectrum.o source.o optics.o approximation.o

all: main spike model out.png test.png

main: $(OBJS)

spike: approximation.o

model: optics.o approximation.o spectrum.o source.o

out.png: main
	./main

test.png: test.sh model
	./test.sh

clean:
	rm $(OBJS)
	rm main.o 
	rm main

main.o: $(HEADERS)
