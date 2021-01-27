OBJ = obj/bmp.o obj/main.o
FLAGS = -I include

all: obj hw_01

obj:
	mkdir -p obj

obj/main.o: src/main.c include/bmp.h
	gcc -g -c -o obj/main.o $(FLAGS) src/main.c

obj/bmp.o: src/bmp.c include/bmp.h
	gcc -g -c -o obj/bmp.o $(FLAGS) src/bmp.c

hw_01: $(OBJ)
	gcc $(FLAGS) -g -o hw_01 $(OBJ)

clean:
	rm -rf obj hw_01
