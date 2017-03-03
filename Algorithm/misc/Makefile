SOURCES = test.cpp \
		  findIndex.cpp \
		  findRepeat.cpp \
		  findLost.cpp \
		  reverseSequence.cpp \
		  buildArray.cpp

test: $(SOURCES) dep
	g++ -I../util -L../util -o $@ $(SOURCES) -lutil

dep:
	make -C ../util

clean:
	rm -f test

.PHONY: dep clean
