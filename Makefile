#!/bin/bash
CC=gcc
RM=rm -f

SRC_PATH=src
INC_PATH=include

INCS=$(foreach d, $(INC_PATH), -I$d)

CFLAGS=-fPIC -march=native -Wall $(MODE) $(INCS)
LDFLAGS=-lpthread -lm

FILE_PREFIX=.c
OBJ=.o

SOURCES=main.c $(SRC_PATH)/ordered_array.c $(SRC_PATH)/plactic_matroid.c
OBJECTS=$(SOURCES:$(FILE_PREFIX)=$(OBJ))

EXECUTABLE=test

MODE=$(DEBUG)

RELEASE=-O2
DEBUG=-g 

all: $(SOURCES) $(EXECUTABLE)
	$(CC) $(CFLAGS) $(OBJECTS) -o $(EXECUTABLE) $(LDFLAGS)

$(EXECUTABLE):$(OBJECTS)

%$(OBJ): %FILE_PREFIX
	$(CC) $(CFLAGS) $< $@ $(LDFLAGS)

clean:
	$(RM) $(OBJECTS) $(SOLIB)
