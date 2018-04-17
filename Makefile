#!/bin/bash
CC=gcc
RM=rm -f

SRC_PATH=src
INC_PATH=include
BUILD_PATH=.

#BUILD_PATH=build

INCS=$(foreach d, $(INC_PATH), -I$d)

CFLAGS=-fPIC -march=native -Wall $(MODE) $(INCS)
LDFLAGS=-lpthread -lm

FILE_PREFIX=.c
OBJ=.o

SOURCES=$(SRC_PATH)/main.c $(SRC_PATH)/ordered_array.c $(SRC_PATH)/semistandard_tableaux.c $(SRC_PATH)/identity_testing.c $(SRC_PATH)/hashmap.c
OBJS=$(subst $(SRC_PATH),$(BUILD_PATH),$(SOURCES))
OBJECTS=$(OBJS:$(FILE_PREFIX)=$(OBJ))


EXECUTABLE=$(BUILD_PATH)/test

MODE=$(DEBUG)

RELEASE=-O2
DEBUG=-g 

all: $(SOURCES) $(EXECUTABLE)
	$(CC) $(CFLAGS) $(OBJECTS) -o $(EXECUTABLE) $(LDFLAGS)

$(EXECUTABLE):$(OBJECTS)

$(BUILD_PATH)/%$(OBJ): $(SRC_PATH)/%$(FILE_PREFIX)
	$(CC) $(CFLAGS) -c $< -o $@ $(LDFLAGS)

clean:
	$(RM) $(OBJECTS) $(SOLIB)
