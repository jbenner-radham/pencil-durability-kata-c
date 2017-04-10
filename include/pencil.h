#include <stdio.h>
#include <string.h>

char * pencil_write_to_paper(const char *text, char *restrict paper)
{
    if (strlen(text) >= BUFSIZ) {
        return paper;
    }

    return strncpy(paper, text, BUFSIZ);
}
