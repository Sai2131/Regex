CC = clang
CFLAGS = -Wall -Wextra

SRCS = $(wildcard *.c)
OBJS = $(SRCS:.c=.o)
TARGET = nfa

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)
