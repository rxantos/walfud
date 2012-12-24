

cc:=g++
flag:=-Wall -g -std=c++11

rebuild:
	$(MAKE) -B main

main : build/main.o
	$(cc) $(flag) -o $@ $^
	mv $@ build
build/main.o : main.cc
	$(cc) $(flag) -c -o $@ $<


test :
run :
	build/main
gdb :
	gdb build/main
	
