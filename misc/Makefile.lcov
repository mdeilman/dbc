#
# Makefile for the LCOV example program.
#
# Make targets:
#   - example: compile the example program
#   - output:  run test cases on example program and create HTML output
#   - clean:   clean up directory
#

CC      := gcc
CFLAGS  := -Wall -I. -fprofile-arcs -ftest-coverage

#LCOV    := ../bin/lcov
#GENHTML := ../bin/genhtml
#GENDESC := ../bin/gendesc
#GENPNG  := ../bin/genpng

LCOV    := lcov
GENHTML := genhtml
GENDESC := gendesc

.PHONY: clean output test_noargs

all: output

dbc: dbc.c dbc.h
	$(CC) $(CFLAGS) dbc.c -o dbc.exe -lgcov

output: dbc descriptions test_noargs
	@echo
	@echo '*'
	@echo '* Generating HTML output'
	@echo '*'
	@echo
	$(GENHTML) trace_noargs.info --output-directory output --title "DBC example" \
		   --show-details --description-file descriptions \
		   --legend
	@echo
	@echo '*'
	@echo '* See '`pwd`/output/index.html
	@echo '*'
	@echo

descriptions: descriptions.txt
	$(GENDESC) descriptions.txt -o descriptions

all_tests: test_noargs

test_noargs:
	@echo
	@echo '*'
	@echo '* Test case 1: running ./dbc without parameters'
	@echo '*'
	@echo
	$(LCOV) --zerocounters --directory .
	./dbc
	$(LCOV) --capture --directory . --output-file trace_noargs.info --test-name test_noargs --no-external

clean:
	rm -rf *.o *.bb *.bbg *.da *.gcno *.gcda *.info output dbc.exe \
	descriptions

