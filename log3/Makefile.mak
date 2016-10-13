all: buggy_code 

buggy_code: logmain.o loglib.o 
	gcc logmain.o loglib.o -o buggy_code
	
logmain.o: logmain.c
	gcc -c logmain.c
	
loglib.o: loglib.c
	gcc -c loglib.c

clean: 
	rm -rf *.o buggy_code