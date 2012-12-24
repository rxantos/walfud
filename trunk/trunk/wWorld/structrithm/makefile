

cc:=g++
flag:=-Wall -g -std=c++11

structrithm : structrithm.o string.o convert.o
	$(cc) $(flag) -o $@ $^
structrithm.o : structrithm.cc
	$(cc) $(flag) -c -o $@ $<
string.o : structure/string.cc
	$(cc) $(flag) -c -o $@ $<
convert.o : ../utils/convert.cc
	$(cc) $(flag) -c -o $@ $<
