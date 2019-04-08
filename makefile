CXX=g++
RM=rm -f bin/*
CPPFLAGS=-g -O3 -Wall

OBJS=src/*

all: PermutationTester

PermutationTester: $(OBJS)
	$(CXX) $(CPPFLAGS) PermutationTester.cxx -o bin/PermutationTester $(OBJS)

clean:
	$(RM)
