
CFLAGS+=-std=c11
CFLAGS+=-Wall -Wextra -Wpedantic
CFLAGS+=-Wwrite-strings -Wstack-usage=1024 -Wfloat-equal -Waggregate-return -Winline

driver: driver.o polynomial.o

.PHONY: clean debug

clean:
	-rm *.o

debug: CFLAGS+=-g
debug: driver
