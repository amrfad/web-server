all:
	gcc -o nihilon *.c *.h -lz
debug:
	gcc -g -DDEBUG -o nihilon *.c *.h -lz
