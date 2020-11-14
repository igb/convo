convomake: main.c
	gcc -o convo main.c -I.

clean:
	rm convo.o
