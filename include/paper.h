#ifndef PAPER_H
#define PAPER_H

size_t paper_word_count(char *paper)
{
    size_t count = 0;
    char *ptr = paper;

    do {
        if (!*ptr) {
            break;
        }

        // Lookback and verify we don't have a NUL pointer then check that we
        // aren't currently on a space. This finds the first word.
        if (*(ptr - 1) == '\0' && *ptr != KATA_SPACE) {
            count += 1;
        }

        // Lookback and see if the prior character was a space then check that
        // we aren't currently on a space. This finds subsequent words.
        if (*(ptr - 1) == KATA_SPACE && *ptr != KATA_SPACE) {
            count += 1;
        }
    } while (*(++ptr));

    return count;
}

#endif // PAPER_H
