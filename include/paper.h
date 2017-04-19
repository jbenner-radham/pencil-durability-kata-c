#ifndef PAPER_H
#define PAPER_H

#include <stdbool.h>

bool paper_is_first_word(char *ptr)
{
    // Lookback and verify we don't have a NUL then check that we aren't
    // currently on a space.
    return (*(ptr - 1) == KATA_NUL && *ptr != KATA_SPACE);
}

bool paper_is_subsequent_word(char *ptr)
{
    // Lookback and see if the prior character was a space then check that
    // we aren't currently on a space.
    return (*(ptr - 1) == KATA_SPACE && *ptr != KATA_SPACE);
}

size_t paper_word_count(char *paper)
{
    size_t count = 0;
    char *ptr = paper;

    do {
        if (!*ptr) {
            break;
        }

        if (paper_is_first_word(ptr) || paper_is_subsequent_word(ptr)) {
            count += 1;
        }
    } while (*(++ptr));

    return count;
}

#endif // PAPER_H
