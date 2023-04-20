CC=gcc
CFLAGS=-Isrc/Include
LIBS=-Lsrc/lib -lmingw32 -lSDL2main -lSDL2

SRCS=test.c src\bullets.c src\game_mechanics.c src\graphics.c src\player.c src\zombies.c
OBJS=$(SRCS:.c=.o)

test: $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o test $(LIBS)

clean:
	del $(OBJS) test.exe
