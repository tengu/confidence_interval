
#
# usage: make clean all test
#

all::
MODULE_NAME=confidence_interval
EXE=$(MODULE_NAME)
include swig.mk
all:: swig-all $(EXE)

clean: swig-clean
	rm -f $(EXE)

CFLAGS+=-Wall
LDFLAGS+=-lm

$(EXE):
	cc -DBUILD_COMMAND  $(MODULE_NAME).c  -lm  -o $(EXE) 

test: test-cmd test-pl

test-cmd: $(EXE)
	./$(EXE) 2 10 0.1
	./$(EXE) 20 100 0.1
	./$(EXE) 200 1000 0.1
	./$(EXE) 200 1000 0.1
	./$(EXE) 2000 10000 0.1

tt:
	@echo $(IFLAGS)

test-pl:
	./test.pl

e:
	cc  -I/usr/lib/perl/5.10/CORE -Wall   -E -o $(MODULE_NAME)_wrap.E $(MODULE_NAME)_wrap.c

