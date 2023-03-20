CC=gcc
CFLAGS=-Wall
LIB=libzad1
REPL=replzad2.c
BINS=replzad2.c dllmanager.h

all:
	make lib_static
	make lib_shared
	make exe_static
	make exe_shared
	make exe_dlopen

lib_static: $(LIB).c
	$(CC) $(CFLAGS) $(OPT_FLAGS) -c $(LIB).c
	ar cr $(LIB).a $(LIB).o

lib_shared: $(LIB).c
	$(CC) $(CFLAGS) $(OPT_FLAGS) -c -fPIC $(LIB).c
	$(CC) $(CFLAGS) $(OPT_FLAGS) -shared -o $(LIB).so $(LIB).o

exe_static: $(LIB).c $(BINS)
	$(CC) $(CFLAGS) $(OPT_FLAGS) $(REPL) -o replzad2_static.exe -L . $(LIB).a
exe_shared: $(LIB).c $(BINS)
	$(CC) $(CFLAGS) $(OPT_FLAGS) $(REPL) -o replzad2_shared.exe -L . $(LIB).so
exe_dlopen: $(LIB).c $(BINS)
	$(CC) $(CFLAGS) $(OPT_FLAGS) $(REPL) -o replzad2_dlopen.exe -ldl -D USE_DLL

test:
	sudo mv libzad1.so /usr/local/lib
	make create_test
	./replzad2_static.exe < tests.in > results_static.txt 2> /dev/null
	./replzad2_shared.exe < tests.in > results_shared.txt 2> /dev/null
	./replzad2_dlopen.exe < tests.in > results_dynamic.txt 2> /dev/null
create_test:
	echo "init 40" > tests.in
	echo "count Makefile" >> tests.in
	echo "count dllmanager.h" >> tests.in
	echo "count libzad1.c" >> tests.in
	echo "count libzad1.h" >> tests.in
	echo "count libzad1_so.h" >> tests.in
	echo "count replzad2.c" >> tests.in
	echo "show 0" >> tests.in
	echo "show 1">> tests.in
	echo "show 2">> tests.in
	echo "delete 2">>tests.in
	echo "delete 2">>tests.in
	echo "destroy" >> tests.in
	echo "quit" >> tests.in

create_raport:
	make test
	rm -f test.in

clean:
	rm -f *.o *.gch *.a *.so *.txt *.exe tests.in