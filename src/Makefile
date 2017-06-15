CC:=g++
flags:=-Wall -Wextra -pedantic -std=c++1z
dflags:=-ggdb3
cflags:=-c $(dflags)
plugindir:=$(PWD)

name:=main

default:main

fileManager.o:fileManager.cc
	$(CC) $(cflags) $(flags) fileManager.cc

stuff/libGreetPlugin.so:greetPlugin.o hello.o bye.o fileManager.o
	$(CC) -shared -o stuff/libGreetPlugin.so fileManager.o greetPlugin.o hello.o bye.o

greetPlugin.o:greetPlugin.cc
	$(CC) $(cflags) $(flags) -fPIC greetPlugin.cc

hello.o:hello.cc
	$(CC) $(cflags) $(flags) -fPIC hello.cc

bye.o:bye.cc
	$(CC) $(cflags) $(flags) -fPIC bye.cc

stuff/libStuffPlugin.so:stuffPlugin.o thing.o stuff.o
	$(CC) -shared -o stuff/libStuffPlugin.so stuffPlugin.o thing.o stuff.o fileManager.o

stuffPlugin.o:stuffPlugin.cc
	$(CC) $(cflags) $(flags) -fPIC stuffPlugin.cc

thing.o:thing.cc
	$(CC) $(cflags) $(flags) -fPIC thing.cc

stuff.o:stuff.cc
	$(CC) $(cflags) $(flags) -fPIC stuff.cc

#you either need to use-
#need to export as:
#export LD_LIBRARY_PATH=$(PWD):$(LD_LIBRARY_PATH)
#and use compiling as:
#$(CC) -L. main.o -o $(name) -lHelloPlugin
#or use rpath as:
#$(CC) -L. -Wl,-rpath=$(PWD) main.o -o $(name) -lHelloPlugin
$(name):$(name).o stuff/libGreetPlugin.so stuff/libStuffPlugin.so fileManager.o pluginManager.hh
	$(CC) -L$(plugindir) -Wl,-rpath=$$ORIGIN $(name).o fileManager.o -o $(name) -ldl

$(name).o:$(name).cc
	$(CC) $(cflags) $(flags) $(name).cc

grind:$(name)
	valgrind --track-origins=yes --leak-check=yes ./$(name)

clean:
	rm *.so *.o *.a core $(name) stuff/*

