CC:=g++
flags:=-Wall -std=c++11 -fPIC
dflags:=-ggdb3
cflags:=-c

name:=main

default:main

libHelloPlugin.so:helloPlugin.o
	$(CC) -shared -o libHelloPlugin.so helloPlugin.o

helloPlugin.o:helloPlugin.cc
	$(CC) $(cflags) $(flags) -fPIC helloPlugin.cc

#you either need to use-
#need to export as:
#export LD_LIBRARY_PATH=$(PWD):$(LD_LIBRARY_PATH)
#and use compiling as:
#$(CC) -L. main.o -o $(name) -lHelloPlugin
#or use rpath as:
#$(CC) -L. -Wl,-rpath=$(PWD) main.o -o $(name) -lHelloPlugin
main:main.o libHelloPlugin.so
	$(CC) -L. -Wl,-rpath=$(PWD) main.o -o $(name) -lHelloPlugin

main.o:main.cc
	$(CC) $(cflags) $(flags) main.cc

clean:
	rm *.so *.o core $(name)

