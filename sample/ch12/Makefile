# Makefile for csapp chapter 12

# mofaph@gmail.com
# 2013-8-10

CC = gcc
CFLAGS = -Wall
INCLUDES += -I../../common
LIBS += -lpthread

OBJS += csapp.o
OBJS += hello.o
OBJS += echoservert.o
OBJS += echo.o

PROGRAMS += hello
PROGRAMS += echoservert

PHONY += all
PHONY += clean

csapp_h = ../../common/csapp.h
csapp_c = ../../common/csapp.c

.PHONY: $(PHONY)

all: $(PROGRAMS)

hello: hello.o csapp.o
	$(CC) $(CFLAGS) $^ $(LIBS) -o $@

hello.o: hello.c ../../common/csapp.h
	$(CC) $(CFLAGS) -I../../common -c $< -o $@

csapp.o: ../../common/csapp.c ../../common/csapp.h
	$(CC) $(CFLAGS) -I../../common -c $< -o $@

echoservert: echoservert.o csapp.o echo.o
	$(CC) $(CFLAGS) $^ $(LIBS) -o $@

echoservert.o: echoservert.c $(csapp_h)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

echo.o: ../ch11/echo.c $(csapp_h)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -f $(OBJS) $(PROGRAMS)
