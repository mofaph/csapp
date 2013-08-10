# Makefile for csapp chapter 12

# mofaph@gmail.com
# 2013-8-10

CC = gcc
CFLAGS = -Wall
LIBS += -lpthread

OBJS += csapp.o
OBJS += hello.o

PROGRAMS += hello

PHONY += all
PHONY += clean

.PHONY: $(PHONY)

all: $(PROGRAMS)

hello: hello.o csapp.o
	$(CC) $(CFLAGS) $^ $(LIBS) -o $@

hello.o: hello.c ../../common/csapp.h
	$(CC) $(CFLAGS) -I../../common -c $< -o $@

csapp.o: ../../common/csapp.c ../../common/csapp.h
	$(CC) $(CFLAGS) -I../../common -c $< -o $@

clean:
	rm -f $(OBJS) $(PROGRAMS)
