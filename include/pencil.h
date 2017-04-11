#include <stdio.h>
#include <string.h>

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
    return (character != PENCIL_SPACE) ? 1 : 0;
}

char * pencil_write_to_paper(const char *text, char *restrict paper)
{
    if (strlen(text) >= BUFSIZ) {
        return paper;
    }

    return strncat(paper, text, BUFSIZ);
}
