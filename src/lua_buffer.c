// =====================================================================================
//
//       Filename:  lua_buffer.c
//         Author:  LeeoNix
//        Created:  2013-11-12 19:45:12
//
//    Description:
//
// =====================================================================================

#include <limits.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "lua_buffer.h"

int buffer_init(buffer_t *b, int l)
{
    b->str_size = 0;
    b->pos = 0;

    b->buf = (char *) malloc(l);
    if (b->buf == NULL)
    {
        b->buf_size = 0;
        return 0;
    }

    b->buf_size = l;
    return 1;
}

void close_buffer(buffer_t *b)
{
    free(b->buf);
    b->buf = NULL;
    b->buf_size = 0;
    b->pos = 0;
    b->str_size = 0;
}

buffer_t *new_buffer()
{
    buffer_t *b = (buffer_t *) malloc(sizeof(buffer_t));
    if (b != NULL)
    {
        if (buffer_init(b, DEFAULT_BUFSIZ))
            return b;
        else
            free(b);
    }
    return NULL;
}

buffer_t *copy_to_buffer_len(const char *c, int l)
{
    int bufl;
    buffer_t *b = (buffer_t *) malloc(sizeof(buffer_t));
    if (b == NULL)
        return NULL;

    bufl = l + 1;
    b->buf = (char *) malloc(bufl);
    if (b->buf == NULL)
    {
        free(b);
        return NULL;
    }

    memcpy(b->buf, c, bufl);
    b->buf_size = bufl;
    b->str_size = b->pos = l;
    return b;
}

void free_buffer(buffer_t *b)
{
    free(b->buf);
    free(b);
}

static int check_buf_size(buffer_t *b, int l)
{
    int newl = b->pos + l;
    if (newl >= b->buf_size)
    {
        char *newbuf;
        b->buf_size *= 2;
        if (b->buf_size <= newl)
        {
            assert(newl + 1 < INT_MAX);
            b->buf_size = newl + 1;
        }
        newbuf = (char *) realloc(b->buf, b->buf_size);
        if (!newbuf)
        {
            close_buffer(b);
            return 0;
        }
        b->buf = newbuf;
    }
    return 1;
}

int buffer_add_char(buffer_t *b, const char c)
{
    int l = sizeof(char);
    if (!check_buf_size(b, l))
        return 0;

    b->buf[b->pos] = c;
    assert(b->pos + l < INT_MAX);
    b->pos += l;
    if (b->str_size < b->pos)
    {
        b->str_size = b->pos;
    }
    return l;
}

int buffer_add_str(buffer_t *b, const char *c, int l)
{
    if (l == 0 || !check_buf_size(b, l))
        return 0;

    if (b->str_size < b->pos)
    {
        memset(b->buf + b->str_size, 0, (b->pos - b->str_size) * sizeof(char));
    }
    memcpy(b->buf + b->pos, c, l);
    assert(b->pos + l < INT_MAX);
    b->pos += l;

    if (b->str_size < b->pos)
    {
        b->str_size = b->pos;
    }

    return l;
}

