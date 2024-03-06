CFLAGS=-Wall

clean:
	rm -f ex1
	rm -f ex3
	rm -f ex4
	rm -f ex6
	rm -f ex7
	rm -f ex8
	rm -f ex9
	rm -f ex10
	rm -f ex11
	rm -f ex12
	rm -f ex13
	rm -f ex14
	rm -f ex15
	rm -f ex16
	rm -f ex17
	rm -f ex18
run:
	./ex1
	./ex3
all:
	gcc -o ex1 ex1.c
	gcc -o ex3 ex3.c
	gcc -o ex4 ex4.c
	gcc -o ex6 ex6.c
	gcc -o ex7 ex7.c
	gcc -o ex8 ex8.c
	gcc -o ex9 ex9.c
	gcc -o ex10 ex10.c
	gcc -o ex11 ex11.c
	gcc -o ex12 ex12.c
	gcc -o ex13 ex13.c
	gcc -o ex14 ex14.c
	gcc -o ex15 ex15.c
	gcc -o ex16 ex16.c
	gcc -o ex17 ex17.c
	gcc -o ex18 ex18.c
