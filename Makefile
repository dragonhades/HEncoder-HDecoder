all: HEncode HDecode

HEncode: HEncode.o tools.o
	g++ -std=c++14 HEncode.o tools.o -o HEncode

HDecode: HDecode.o tools.o
	g++ -std=c++14 HDecode.o tools.o -o HDecode

tools.o: tools.cc tools.h
	g++ -std=c++14 -c tools.cc

HEncode.o: HEncode.cc tools.h
	g++ -std=c++14 -c HEncode.cc

HDecode.o: HDecode.cc tools.h
	g++ -std=c++14 -c HDecode.cc

.PHONY: clean

clean:
	rm *.o HDecode HEncode
