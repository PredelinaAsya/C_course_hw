OBJ = obj/point_list.o obj/clist.o obj/main.o
FLAGS = -I include

all: obj lab_05

obj:
	mkdir -p obj

obj/main.o: src/main.c include/point_list.h include/clist.h
	gcc -g -c -o obj/main.o $(FLAGS) src/main.c

obj/clist.o: src/clist.c include/clist.h
	gcc -g -c -o obj/clist.o $(FLAGS) src/clist.c

obj/point_list.o: src/point_list.c include/point_list.h include/clist.h
	gcc -g -c -o obj/point_list.o $(FLAGS) src/point_list.c

lab_05: $(OBJ)
	gcc $(FLAGS) -g -o lab_05 $(OBJ)

clean:
	rm -rf obj lab_05
