CC=gcc
CFLAGS=-Isrc/Include
LIBS=-Lsrc/lib -lmingw32 -lSDL2main -lSDL2

SRCS=main.c src\bullets.c src\game_mechanics.c src\graphics.c src\player.c src\zombies.c
OBJS=$(SRCS:.c=.o)

game: $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o test $(LIBS)

clean:
	del $(OBJS) test.exe
