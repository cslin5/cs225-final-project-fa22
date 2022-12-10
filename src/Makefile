CXX=clang++
CXX_FLAGS=-std=c++20 -g -O0 -Wall -Wextra -Werror -Iincludes/

exec: bin/exec
tests: bin/tests

bin/exec: src/main.cpp includes/illini_book.hpp src/illini_book.cc includes/utilities.hpp src/utilities.cc
	${CXX} ${CXX_FLAGS} src/driver.cc src/illini_book.cc src/utilities.cc -o bin/exec

bin/tests: tests/tests.cc includes/illini_book.hpp src/illini_book.cc includes/utilities.hpp src/utilities.cc
	${CXX} ${CXX_FLAGS} tests/tests.cc src/driver.cc src/illini_book.cc src/utilities.cc -o bin/tests

.DEFAULT_GOAL := exec
.PHONY: clean exec tests

clean:
	rm -rf bin/*
 
