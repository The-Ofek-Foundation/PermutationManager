CC=gcc
CXX=g++
RM=rm -f bin/*
CPPFLAGS=-g -O3 -Wall

OBJS=src/*

all: PermutationTester

PermutationTester: $(OBJS)
	$(CXX) $(CPPFLAGS) -o bin/PermutationTester $(OBJS)

PermutationTester.o: PermutationTester.cxx PermutationManager.hxx

PermutationManager.o: PermutationManager.hxx PermutationManager.cxx

clean:
	$(RM) $(OBJS)

distclean: clean
	$(RM) PermutationTester