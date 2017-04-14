STD = -std=gnu99

# > If there are C compiler options that must be used for proper compilation of
# > certain files, do not include them in CFLAGS. Users expect to be able to
# > specify CFLAGS freely themselves. Instead, arrange to pass the necessary
# > options to the C compiler independently of CFLAGS, by writing them
# > explicitly in the compilation commands or by defining an implicit rule [...]
CFLAGS = $(STD) -O2 -Wall -Wextra -Iinclude
TEST_BINARY = kata

# The first target listed acts as the default.
test:
	@ $(CC) $(CFLAGS) `pkg-config --libs --cflags check` -o kata tests/kata.c && ./"${TEST_BINARY}"

clean:
	@ rm -f "${TEST_BINARY}"

.PHONEY: clean test
