#define _POSIX_C_SOURCE 200809L

#include <assert.h>
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

unsigned int pencil_str_degradation(const char *text)
{
    unsigned int degradation = 0;
    size_t text_length = strnlen(text, BUFSIZ);
    char character;

    for (size_t pos = 0; pos < text_length; ++pos) {
        character = text[pos];
        degradation += pencil_degradation(character);
    }

    return degradation;
}

char * pencil_write_to_paper(Pencil *pencil, const char *text, char *restrict paper)
{
    size_t text_length = strnlen(text, BUFSIZ);

    assert(text_length < BUFSIZ);

    unsigned int degradation = pencil_str_degradation(text);

    if (pencil->point_durability >= degradation) {
        pencil->point_durability -= degradation;

        return strncat(paper, text, BUFSIZ);
    }

    char text_buffer[BUFSIZ] = {0};
    char character;
    unsigned int character_degradation;
    size_t pos;

    for (pos = 0; pos < text_length; ++pos) {
        character = text[pos];
        character_degradation = pencil_degradation(character);

        // Write the character if we have enough point durability.
        if (pencil->point_durability >= character_degradation) {
            pencil->point_durability -= character_degradation;
            text_buffer[pos] = text[pos];
            continue;
        }

        // Write a space if we don't have enough point durability.
        text_buffer[pos] = ' ';
    }

    text_buffer[pos] = '\0';

    return strncat(paper, text_buffer, BUFSIZ);
}
