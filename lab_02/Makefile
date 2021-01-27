OBJ = obj/str.o obj/test_str.o obj/test.o
FLAGS = -I include

all: obj lab_02

obj:
	mkdir -p obj

obj/str.o: src/str.c include/str.h
	gcc -c -o obj/str.o $(FLAGS) src/str.c

obj/test_str.o: src/test_str.c include/test_str.h include/str.h
	gcc -c -o obj/test_str.o $(FLAGS) src/test_str.c

obj/test.o: src/test.c include/test_str.h
	gcc -c -o obj/test.o $(FLAGS) src/test.c

lab_02: $(OBJ)
	gcc $(FLAGS) -o lab_02 $(OBJ)

clean:
	rm -rf obj lab_02
