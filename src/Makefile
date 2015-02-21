CC:=g++
flags:=-Wall -std=c++11 -fPIC
dflags:=-ggdb3
cflags:=-c

name:=main

default:main

libHelloPlugin.so:helloPlugin.o
	$(CC) -shared -fPIC -Wl,-soname,libHelloPlugin.so.1 -o libHelloPlugin.so.1.0 helloPlugin.o -lc
	sudo ln -sf /usr/lib/libctest.so.1.0 /usr/lib/libctest.so.1
	sudo ln -sf /usr/lib/libctest.so.1.0 /usr/lib/libctest.so

helloPlugin.o:helloPlugin.cc
	$(CC) $(cflags) $(flags) helloPlugin.cc

main:main.o libHelloPlugin.so
	$(CC) main.o -o $(name) -I. -L. -lHelloPlugin

main.o:main.cc
	$(CC) $(cflags) $(flags) main.cc

clean:
	rm *.a *.o core $(name)

