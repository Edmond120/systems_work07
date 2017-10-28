SRC := random.c test.c
OBJ := $(SRC:.c=.o)

all: random

$(OBJ): Makefile random.h

random: $(OBJ)
	@echo "[LD] $@"
	@$(CC) -g $(LDFLAGS) -o $@ $^

%.o: %.c
	@echo "[CC] $@"
	@$(CC) -g $(CFLAGS) -c -o $@ $<

clean:
	rm -f random numbers.txt $(OBJ)

run: random
	./random

