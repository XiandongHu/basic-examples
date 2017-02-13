MODULE = hello
ALL_OBJS = hello.o

all: $(MODULE)

include rules.mk

$(MODULE): $(ALL_OBJS)
	$(XCC) -o $@ $(ALL_OBJS)

clean:
	rm -f $(MODULE)
	rm -f *.o
	rm -f *.d

.PHONY: all clean
