OBJ = obj/main.o obj/mergesort.o
FLAGS = -I include

all: obj lab_03

obj:
	mkdir -p obj

obj/main.o: src/main.c include/mergesort.h
	gcc -c -o obj/main.o $(FLAGS) src/main.c

obj/mergesort.o: src/mergesort.c include/mergesort.h
	gcc -c -o obj/mergesort.o $(FLAGS) src/mergesort.c

lab_03: $(OBJ)
	gcc $(FLAGS) -o lab_03 $(OBJ)

clean:
	rm -rf obj lab_03
