REGEXBUILD = ../build/cRegex.a

all: main.o $(REGEXBUILD) 
	clang -o main main.o $(REGEXBUILD)

main.o:
	clang -c main.c

$(REGEXBUILD):
	cd .. && $(MAKE)

clean:
	rm -f *.o main