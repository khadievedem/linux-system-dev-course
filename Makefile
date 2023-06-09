CC=gcc
LD_LIBRARY_PATH="./lib/"  



all: bin

bin: src/main.c src/hello.h lib
	$(CC) src/main.c -fPIC -ldl -o target/a.out

lib: src/hello.c src/hello.h
	$(CC) --shared src/hello.c -fPIC -o lib/libhello.so

clean:
	-rm target/a.out lib/libhello.so 2>/dev/null

.PHONY: all lib clean
