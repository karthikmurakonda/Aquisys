CC = gcc	# Compiler is gcc

SRCS := $(wildcard *.c)
OBJS := $(SRCS:%.c=%.o)

build: ${OBJS}
	${CC} ${OBJS} -o run

%.o: %.c
	${CC} -c $< -o $@;

clean:
	rm -f *.o run

clean-appdata:
	rm -f .appdata.dat