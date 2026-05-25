cflags = -std=c99 -O2 

includes = -I ../iostring -I ../structures/tablashash/cuadratica

source = $(wildcard *.c) ../structures/tablashash/cuadratica/HashQ.c

output = ../../bin/practica9

build :
	gcc $(cflags) $(source) -o $(output) $(includes)
	@echo "Compilo Exitosamente!!!"

run :
	$(output).exe