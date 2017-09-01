RM=cmd \/C del
#RM = rm -f
NAME=dbc
TIME=ptime
BUILD=../build/
EXE=.exe
OBJ=.o
EXT=.c
CC=gcc
CFLAGS += -g -Wall -Wextra -std=c99
CFLAGS += -fdiagnostics-color=always
#CFLAGS += -pedantic
TFLAG +=
#INCL=-Ic:/mingw/include
LIB=

$(NAME): $(NAME)$(OBJ)
	$(CC) $(INCL) -o $(BUILD)$(NAME)$(EXE) $(BUILD)$(NAME)$(OBJ) $(LIB)

$(NAME)$(OBJ): $(NAME)$(EXT)
	$(CC) $(CFLAGS) $(INCL) -c $(NAME)$(EXT) -o $(BUILD)$(NAME)$(OBJ)

# Clean up afterwards
clean:
	$(RM) $(BUILD)$(NAME)$(OBJ)
	$(RM) $(BUILD)$(NAME)$(EXE)

# Simple run
run:
	$(BUILD)$(NAME)$(EXE)

# Run time
time:
	$(TIME) $(BUILD)$(NAME)$(EXE)

# Needs a test flag to be implemented
check:
	$(BUILD)$(NAME)$(EXE) $(TFLAG)
