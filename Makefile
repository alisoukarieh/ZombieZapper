game:
	gcc -Isrc/Include -Lsrc/lib -o main main.c window.c player.c -lmingw32 -lSDL2main -lSDL2 
	#gcc -I./ -I src/include -L src/lib -o main main.c window.c player.c -lSDL2main -lSDL2 
	# -lSDL2_image -lSDL2_ttf -lSDL2_mixer -lm

test : 
	gcc -Isrc/Include -Lsrc/lib -o test test.c graphics.c entities.c -lmingw32 -lSDL2main -lSDL2 
	