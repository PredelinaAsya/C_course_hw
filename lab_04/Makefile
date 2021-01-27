OBJ = obj/clist.o obj/main.o
FLAGS = -I include

all: obj lab_04

obj:
	mkdir -p obj

obj/main.o: src/main.c include/clist.h
	gcc -g -c -o obj/main.o $(FLAGS) src/main.c

obj/clist.o: src/clist.c include/clist.h
	gcc -g -c -o obj/clist.o $(FLAGS) src/clist.c

lab_04: $(OBJ)
	gcc $(FLAGS) -g -o lab_04 $(OBJ)

clean:
	rm -rf obj lab_04
