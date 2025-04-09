.SUFFIXES: .c .o
VPATH := glue


all: VBoxCAPIGlue.o

.c.o:
	cc -c $< -o $@  -Iinclude
