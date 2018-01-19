#!/bin/bash
CC=gcc
RM=rm -f

SRC_PATH=src
INC_PATH=include

INCS=$(foreach d, $(INC_PATH), -I$d)

CFLAGS=-fPIC -march=native -Wall $(MODE) $(INCS)
SFLAGS=-shared
LDFLAGS=-lpthread -lm

FILE_PREFIX=.c
OBJ=.o

SOURCES=main.c $(SRC_PATH)/ordered_array.c $(SRC_PATH)/plactic_matroid.c
OBJECTS=$(SOURCES:$(FILE_PREFIX)=$(OBJ))

EXECUTABLE=test

SOLIB=libplacticmonoids.so

MODE=$(RELEASE)

RELEASE=-O2
DEBUG=-g 

all: $(SOURCES) $(SOLIB)
	$(CC) $(CFLAGS) $(OBJECTS) $(SFLAGS) -o $(SOLIB) $(LDFLAGS)

$(SOLIB):$(OBJECTS)

%$(OBJ): %FILE_PREFIX
	$(CC) $(CFLAGS) $< $@ $(LDFLAGS)

clean:
	$(RM) $(OBJECTS) $(SOLIB)
