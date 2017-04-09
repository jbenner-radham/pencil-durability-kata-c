STD = -std=c11

# > If there are C compiler options that must be used for proper compilation of
# > certain files, do not include them in CFLAGS. Users expect to be able to
# > specify CFLAGS freely themselves. Instead, arrange to pass the necessary
# > options to the C compiler independently of CFLAGS, by writing them
# > explicitly in the compilation commands or by defining an implicit rule [...]
CFLAGS = $(STD) -O2 -pedantic -Wall -Wextra -Iinclude -I/usr/local/include/

# The first target listed acts as the default.
test:
	@ $(CC) $(CFLAGS) -o kata tests/kata.c && ./kata

.PHONEY: test
