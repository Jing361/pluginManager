CC:=g++
flags:=-Wall -std=c++11
dflags:=-ggdb3
cflags:=-c $(dflags)
plugindir:=$(PWD)

name:=main

default:main

pluginManager.o:pluginManager.cc
	$(CC) $(cflags) $(flags) pluginManager.cc

libGreetPlugin.so:greetPlugin.o hello.o bye.o
	$(CC) -shared -o stuff/libGreetPlugin.so greetPlugin.o hello.o bye.o

greetPlugin.o:greetPlugin.cc
	$(CC) $(cflags) $(flags) -fPIC greetPlugin.cc

hello.o:hello.cc
	$(CC) $(cflags) $(flags) -fPIC hello.cc

bye.o:bye.cc
	$(CC) $(cflags) $(flags) -fPIC bye.cc

#you either need to use-
#need to export as:
#export LD_LIBRARY_PATH=$(PWD):$(LD_LIBRARY_PATH)
#and use compiling as:
#$(CC) -L. main.o -o $(name) -lHelloPlugin
#or use rpath as:
#$(CC) -L. -Wl,-rpath=$(PWD) main.o -o $(name) -lHelloPlugin
main:main.o libGreetPlugin.so pluginManager.o
	$(CC) -L$(plugindir) -Wl,-rpath=$(plugindir) main.o pluginManager.o -o $(name) -ldl
#$(CC) -L. -Wl,-rpath=$(PWD) main.o pluginManager.o -o $(name) -ldl

main.o:main.cc
	$(CC) $(cflags) $(flags) main.cc

grind:$(name)
	valgrind --track-origins=yes --leak-check=yes ./$(name)

clean:
	rm *.so *.o core $(name)

