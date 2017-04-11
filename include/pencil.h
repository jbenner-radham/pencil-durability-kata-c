#include <stdio.h>
#include <string.h>

typedef struct {
    unsigned int point_durability;
} Pencil;

void pencil_ctor(Pencil *pencil, unsigned int point_durability)
{
    pencil->point_durability = point_durability;
}

char * pencil_write_to_paper(const char *text, char *restrict paper)
{
    if (strlen(text) >= BUFSIZ) {
        return paper;
    }

    return strncat(paper, text, BUFSIZ);
}
