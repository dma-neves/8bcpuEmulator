_DEPS=main.c cpu.h
DEPS=$(patsubst %,src/%,$(_DEPS))

CC=gcc
CFLAGS=-I src

ODIR=obj
_OBJ=main.o cpu.o
OBJ=$(patsubst %,$(ODIR)/%,$(_OBJ))

emulator.out: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

$(ODIR)/%.o: src/%.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

clean:
	rm $(ODIR)/*.o emulator.out