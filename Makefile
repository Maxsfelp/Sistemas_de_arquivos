CC = gcc

CFLAGS = -g

LDFLAGS = -lm -lpthread -Wall

FONTES = $(wildcard *.c)

OBJETOS = $(FONTES:.c=.o)

EXECUTAVEL = fat

all: $(EXECUTAVEL)

$(EXECUTAVEL): $(OBJETOS)
	$(CC) -o $@ $^ $(LDFLAGS)

%.o: %.c
	$(CC) -c $(CFLAGS) $^

clean:
	rm -rf *.o $(EXECUTAVEL)
