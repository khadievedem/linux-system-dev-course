CC=gcc



all: bin

bin: src/main.c src/hello.h lib
	$(CC) src/main.c -fPIC -Llib -lhello -o target/a.out

lib: src/hello.c src/hello.h
	$(CC) --shared src/hello.c -fPIC -o lib/libhello.so

clean:
	-rm target/a.out lib/libhello.so 2>/dev/null
