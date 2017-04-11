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
    switch (character) {
        case PENCIL_NEWLINE:
        case PENCIL_SPACE:
            return 0;
        default:
            return 1;
    }
}

char * pencil_write_to_paper(const char *text, char *restrict paper)
{
    if (strlen(text) >= BUFSIZ) {
        return paper;
    }

    return strncat(paper, text, BUFSIZ);
}
