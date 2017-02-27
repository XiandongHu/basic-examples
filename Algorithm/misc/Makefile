SOURCES = test.cpp \
		  find.cpp

test: $(SOURCES)
	g++ -I../util -L../util -o $@ $(SOURCES) -lutil

dep:
	make -C ../util

clean:
	rm -f test

.PHONY: dep clean
