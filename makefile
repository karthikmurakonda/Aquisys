CC = gcc	# Compiler is gcc

SRCS := $(wildcard *.c)
OBJS := $(SRCS:%.c=%.o)

build: ${SRCS}
	${CC} ${SRCS} -o run

debug: ${SRCS}
	${CC} -g ${SRCS} -o run

clean:
	rm -f *.o run

clean-appdata:
	rm -f .appdata.dat