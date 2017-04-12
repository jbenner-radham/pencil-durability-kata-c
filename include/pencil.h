#include <ctype.h>
#include <stdio.h>
#include <string.h>

#define PENCIL_NEWLINE '\n'
#define PENCIL_SPACE ' '

typedef struct {
    unsigned int point_durability;
} Pencil;

void pencil_ctor(Pencil *pencil, unsigned int point_durability)
{
    pencil->point_durability = point_durability;
}

unsigned int pencil_degradation(char character)
{
    // Whitespace doesn't degrade the pencil tip.
    if (character == PENCIL_NEWLINE || character == PENCIL_SPACE) {
        return 0;
    }

    // Lowercase letters degrade by a single point.
    if (character == tolower(character)) {
        return 1;
    }

    // Uppercase letters degrade by two points.
    return 2;
}

char * pencil_write_to_paper(const char *text, char *restrict paper)
{
    if (strlen(text) >= BUFSIZ) {
        return paper;
    }

    return strncat(paper, text, BUFSIZ);
}
