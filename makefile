#Command to change environment variable to working directory
#Run before every startup
#export LD_LIBRARY_PATH=`pwd`

#Declaring variables for makefile
CC = clang
CFLAGS = -Wall -std=c99 -pedantic

#
#Rules for makefile
#

#Rule For Full Executable
test: all A1Test1.o libhclib.so all
	$(CC) A1Test1.o -L. -lhclib -o test

#Rule that creates main.o from main.c (main)
A1Test1.o: A1Test1.c hclib.h
	$(CC) $(CFLAGS) -c A1Test1.c -o A1Test1.o

#Rule for making all necessary compilation commands
all: libhclib.so _hclib.so

#Rule that creates shared library from hlib.o dependancy
libhclib.so: hclib.o
	$(CC) hclib.o -shared -o libhclib.so -lm

#Rule that creates object file (hclib.o) from hclib.c dependany
hclib.o: hclib.c
	$(CC) $(CFLAGS) -c hclib.c -fPIC -o hclib.o

#Rule to create _hclib.so file
_hclib.so: hclib_wrap.o
	$(CC) $(CFLAGS) -shared hclib_wrap.o -L. -L/usr/lib/python3.11/config-3.11-x86_64-linux-gnu -lpython3.11 -lhclib -o _hclib.so

#Rule to create hclib_wrap.o file
hclib_wrap.o: hclib_wrap.c
	$(CC) $(CFLAGS) -c hclib_wrap.c -I/usr/include/python3.11/ -fPIC -o hclib_wrap.o

#Rule that creates hclib.py interface file and hclib_wrap.c file
hclib_wrap.c:
	swig -python hclib.i

#Rule to start and run server.py file
server: clean all
	python3 server.py 48849

#Rule that cleans current directory from *.o *.so *.exe *.db hclib_wrap.c hclib.py
clean: 
	rm -f *.o *.so *.exe *.db hclib_wrap.c hclib.py

#Rule that cleans current directory from *.db
d: 
	rm -f *.db