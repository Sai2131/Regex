REGEXBUILD = ../build/cRegex.a

all: main.o $(REGEXBUILD) 
	clang -o main main.o $(REGEXBUILD)

example: example.o $(REGEXBUILD) 
	clang -o example example.o $(REGEXBUILD)

main.o: main.c
	clang -c main.c

example.o: example.c
	clang -c example.c

$(REGEXBUILD):
	cd .. && $(MAKE)

lib:
	cd .. && $(MAKE)

clean:
	rm -f *.o main example