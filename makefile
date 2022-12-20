src = src/*.cpp
bin = bin
out = $(bin)/out
obj = ../obj/initialization.o ../obj/draw.o



make: library build run

build:
	g++ $(src) -o $(out) -L$(bin) -ltermDisplay

run:
	./$(out)

library:
	cd obj;\
	gcc -c ../src/termDisplay/*.c -O3;\
	cd ../bin;\
	ar rcs libtermDisplay.a $(obj);\
	cd ../;
