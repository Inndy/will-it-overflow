all:
	gcc overflow.c -D_FORTIFY_SOURCE=0 -o overflow
	./overflow
