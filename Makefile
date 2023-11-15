trz.e: trz_ultraviolence.c trz.ultraviolence.h testy.c
	gcc @opcje trz_ultraviolence.c -o trz.e

brut.e: trz_ultraviolence.c trz.ultraviolence.h testy.c
	gcc @opcje trz_ultraviolence.c -o trz.e

trz.o: trz_ultraviolence.c trz_ultraviolence.h
	gcc trz_ultraviolence.c -c

ary.e: ary.c ary.h przyklad.c
	gcc @opcje ary.c przyklad.c -lm -o ary.e

ary.o: ary.c ary.h
	gcc ary.c -c

clean:
	rm -f *.e
