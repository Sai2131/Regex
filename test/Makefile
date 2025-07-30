REGEXBUILD = ../build/cRegex.a

all: main.o $(REGEXBUILD) 
	clang -o main main.o $(REGEXBUILD)

main.o: main.c
	clang -c main.c

$(REGEXBUILD):
	cd .. && $(MAKE)

lib:
	cd .. && $(MAKE)

clean:
	rm -f *.o main