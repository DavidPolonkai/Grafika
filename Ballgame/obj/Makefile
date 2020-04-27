all:
	gcc -Iinclude/ -c src/model.c -o model.o
	gcc -Iinclude/ -c src/load.c -o load.o
	gcc -Iinclude/ -c src/info.c -o info.o
	gcc -Iinclude/ -c src/draw.c -o draw.o
	gcc -Iinclude/ -c src/transform.c -o transform.o
	ar rcs libobj.a model.o load.o info.o draw.o transform.o
