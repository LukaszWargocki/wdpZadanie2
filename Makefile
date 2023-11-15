brut.e: brut.c
	gcc @opcje brut.c -o brut.e

rozw.e: rozw.c
	gcc @opcje rozw.c -o rozw.e
	
clean:
	rm -f *.e
