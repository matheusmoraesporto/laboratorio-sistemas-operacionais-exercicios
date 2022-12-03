all: teste
teste: teste.o principal.o
	gcc -o teste teste.o principal.o
## Distância inicial deve ser com a tecla <Tab> e não com espaços 
teste.o: teste.c
	gcc -o teste.o -c teste.c -Wall
principal.o: principal.c teste.h
	gcc -o principal.o -c principal.c -Wall
clean:
	rm -rf *.o
mrproper: clean
	rm -rf teste