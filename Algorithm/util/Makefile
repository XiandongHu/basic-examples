LIB = libutil.a
OBJS = util.o

%.o: %.cpp
	g++ -c $< -o $@

$(LIB): $(OBJS)
	rm -f $@
	ar cr $@ $(OBJS)
	rm -f $(OBJS)

clean:
	rm -f $(LIB)

.PHONY: clean
