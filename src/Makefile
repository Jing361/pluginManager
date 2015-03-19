CC:=g++
flags:=-Wall -std=c++11
dflags:=-ggdb3
cflags:=-c $(dflags)
plugindir:=$(PWD)

name:=main

default:main

libPluginManager.a:pluginManager.o fileManager.o
	ar -cvq libPluginManager.a pluginManager.o fileManager.o
	
pluginManager.o:pluginManager.cc
	$(CC) $(cflags) $(flags) pluginManager.cc

fileManager.o:fileManager.cc
	$(CC) $(cflags) $(flags) fileManager.cc

stuff/libGreetPlugin.so:greetPlugin.o hello.o bye.o
	$(CC) -shared -o stuff/libGreetPlugin.so greetPlugin.o hello.o bye.o

greetPlugin.o:greetPlugin.cc
	$(CC) $(cflags) $(flags) -fPIC greetPlugin.cc

hello.o:hello.cc
	$(CC) $(cflags) $(flags) -fPIC hello.cc

bye.o:bye.cc
	$(CC) $(cflags) $(flags) -fPIC bye.cc

stuff/libStuffPlugin.so:stuffPlugin.o thing.o stuff.o
	$(CC) -shared -o stuff/libStuffPlugin.so stuffPlugin.o thing.o stuff.o

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
main:main.o stuff/libGreetPlugin.so stuff/libStuffPlugin.so libPluginManager.a
	$(CC) -L$(plugindir) -Wl,-rpath=$(plugindir) main.o libPluginManager.a -o $(name) -ldl
#$(CC) -L. -Wl,-rpath=$(PWD) main.o pluginManager.o -o $(name) -ldl

main.o:main.cc
	$(CC) $(cflags) $(flags) main.cc

grind:$(name)
	valgrind --track-origins=yes --leak-check=yes ./$(name)

clean:
	rm *.so *.o *.a core $(name) stuff/*

