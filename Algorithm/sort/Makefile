SOURCES = test.cpp \
		  bubble.cpp \
		  insert.cpp \
		  select.cpp \
		  shell.cpp \
		  merge.cpp \
		  quick.cpp \
		  heap.cpp \
		  radix.cpp

test: $(SOURCES) dep
	g++ -I../util -L../util -o $@ $(SOURCES) -lutil

dep:
	make -C ../util

clean:
	rm -f test

.PHONY: dep clean
