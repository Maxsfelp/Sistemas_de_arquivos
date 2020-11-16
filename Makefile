CC = gcc

CFLAGS = -g

LDFLAGS = -lm -lpthread

FONTES = $(wildcard *.c)

OBJETOS = $(FONTES:.c=.o)

EXECUTAVEL = arquivo

all: $(EXECUTAVEL)

$(EXECUTAVEL): $(OBJETOS)
	$(CC) -o $@ $^ $(LDFLAGS)

%.o: %.c
	$(CC) -c $(CFLAGS) $^

clean:
	rm -rf *.o $(EXECUTAVEL)
