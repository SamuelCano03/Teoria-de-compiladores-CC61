#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXLEXEMA 256

#define COMP 256
#define ID 257
#define IF 258
#define ELSE 259
#define NUM 260
#define NUMR 261
#define FUNC 262
#define END 263
#define MOD 264
#define LOOP 265
#define COND 266
#define SUM 267
#define MINUS 268
#define MULT 269
#define DIV 270
#define DIVE 271

struct Handler
{
    FILE *file;
    char lexem[MAXLEXEMA];
};

int lex(struct Handler *h)
{
    size_t i = 0;
    h->lexem[i] = fgetc(h->file);

    if ((h->lexem[i] >= 'a' && h->lexem[i] <= 'z') ||
        (h->lexem[i] >= 'A' && h->lexem[i] <= 'Z') || h->lexem[i] == '_')
    {
        do
        {
            h->lexem[++i] = fgetc(h->file);
        } while ((h->lexem[i] >= 'a' && h->lexem[i] <= 'z') ||
                 (h->lexem[i] >= 'A' && h->lexem[i] <= 'Z') ||
                 (h->lexem[i] >= '0' && h->lexem[i] <= '9') || h->lexem[i] == '_');
        h->lexem[i] = '\0';
        ungetc(h->lexem[i], h->file);
        if (strcmp(h->lexem, "func") == 0)
        {
            return FUNC;
        }
        else if (strcmp(h->lexem, "end") == 0)
        {
            return END;
        }
        else if (strcmp(h->lexem, "mod") == 0)
        {
            return MOD;
        }
        else if (strcmp(h->lexem, "loop") == 0)
        {
            return LOOP;
        }
        else if (strcmp(h->lexem, "cond") == 0)
        {
            return COND;
        }

        return ID;
    }
    if (h->lexem[i] >= '0' && h->lexem[i] <= '9')
    {
        do
        {
            h->lexem[++i] = fgetc(h->file);
        } while (h->lexem[i] >= '0' && h->lexem[i] <= '9');

        if (h->lexem[i] == '.')
        {
            do
            {
                h->lexem[++i] = fgetc(h->file);
            } while (h->lexem[i] >= '0' && h->lexem[i] <= '9');
            if (h->lexem[i] == 'e' || h->lexem[i] == 'E')
            {
                do
                {
                    h->lexem[++i] = fgetc(h->file);
                } while (h->lexem[i] >= '0' && h->lexem[i] <= '9');
            }
            h->lexem[i] = '\0';
            ungetc(h->lexem[i], h->file);
            return NUMR;
        }
        else{

            h->lexem[i] = '\0';
            ungetc(h->lexem[i], h->file);
            return NUM;
        }
    }

    if (h->lexem[i] == '+')
        return SUM;
    if (h->lexem[i] == '-')
        return MINUS;
    if (h->lexem[i] == '*')
        return SUM;
    if (h->lexem[i] == '/')
        return SUM;
    if (h->lexem[i] == '\\')
        return SUM;
    return h->lexem[i] != EOF ? lex(h) : EOF;
}

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        printf("Usage: %s <sourcefile>\n", argv[0]);
        return -1;
    }
    struct Handler *handler = (struct Handler *)malloc(sizeof(struct Handler));
    handler->file = fopen(argv[1], "r");

    int tok;
    while ((tok = lex(handler)) != EOF)
    {
        printf("Lexem (%d): %s\n", tok, handler->lexem);
    }

    fclose(handler->file);
    free(handler);
    return 0;
}