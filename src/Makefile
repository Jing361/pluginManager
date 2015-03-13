CC:=g++
flags:=-Wall -std=c++11
dflags:=-ggdb3
cflags:=-c $(dflags)
plugindir:=$(PWD)

name:=main

default:main

pluginManager.o:pluginManager.cc
	$(CC) $(cflags) $(flags) pluginManager.cc

libHelloPlugin.so:helloPlugin.o hello.o
	$(CC) -shared -o libHelloPlugin.so helloPlugin.o hello.o

helloPlugin.o:helloPlugin.cc
	$(CC) $(cflags) $(flags) -fPIC helloPlugin.cc

hello.o:hello.cc
	$(CC) $(cflags) $(flags) -fPIC hello.cc

#you either need to use-
#need to export as:
#export LD_LIBRARY_PATH=$(PWD):$(LD_LIBRARY_PATH)
#and use compiling as:
#$(CC) -L. main.o -o $(name) -lHelloPlugin
#or use rpath as:
#$(CC) -L. -Wl,-rpath=$(PWD) main.o -o $(name) -lHelloPlugin
main:main.o libHelloPlugin.so pluginManager.o
	$(CC) -L$(plugindir) -Wl,-rpath=$(plugindir) main.o pluginManager.o -o $(name) -ldl
#$(CC) -L. -Wl,-rpath=$(PWD) main.o pluginManager.o -o $(name) -ldl

main.o:main.cc
	$(CC) $(cflags) $(flags) main.cc

grind:$(name)
	valgrind --track-origins=yes --leak-check=yes ./$(name)

clean:
	rm *.so *.o core $(name)

