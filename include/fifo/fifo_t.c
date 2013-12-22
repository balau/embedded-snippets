/*
 * Copyright (c) 2013 Francesco Balducci
 *
 * This file is part of embedded-snippets.
 *
 *    embedded-snippets is free software: you can redistribute it and/or modify
 *    it under the terms of the GNU Lesser General Public License as published by
 *    the Free Software Foundation, either version 3 of the License, or
 *    (at your option) any later version.
 *
 *    embedded-snippets is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *    GNU Lesser General Public License for more details.
 *
 *    You should have received a copy of the GNU Lesser General Public License
 *    along with embedded-snippets.  If not, see <http://www.gnu.org/licenses/>.
 */

/* TODO: check if fifo_t.h has been included. */

#ifndef FIFO_T
#  error FIFO_T needed. e.g. #define FIFO_T uint8_t
#endif

#ifndef FIFO_TNAME
#  error FIFO_TNAME needed. e.g. #define FIFO_TNAME uint8
#endif

void FIFO_CREATE_NAME(init)(
        struct FIFO_STRUCT_NAME *f,
        FIFO_TYPE *buffer,
        size_t size)
{
    f->buffer = buffer;
    f->in = 0;
    f->out = 0;
    f->size = size;
}

static
size_t incr(
        const struct FIFO_STRUCT_NAME *f,
        size_t p)
{
    p = p + 1;
    if (p >= f->size)
    {
        p = 0;
    }
    return p;
}

int FIFO_CREATE_NAME(isempty)(
    const struct FIFO_STRUCT_NAME *f)
{
    return (f->in == f->out)?1:0;
}

int FIFO_CREATE_NAME(isfull)(
    const struct FIFO_STRUCT_NAME *f)
{
    size_t next_in;
    next_in = incr(f, f->in);
    return (next_in == f->out)?1:0;
}

int FIFO_CREATE_NAME(insert)(
    struct FIFO_STRUCT_NAME *f,
    FIFO_TYPE e)
{
    if (FIFO_CREATE_NAME(isfull)(f) == 0)
    {
        size_t in = f->in;
        f->buffer[in] = e;
        f->in = incr(f, in);
        return 0;
    }
    else
    {
        return 1;
    }
}

int FIFO_CREATE_NAME(peek)(
    const struct FIFO_STRUCT_NAME *f,
    FIFO_TYPE *e)
{
    if (FIFO_CREATE_NAME(isempty)(f) == 0)
    {
        *e = f->buffer[f->out];
        return 0;
    }
    else
    {
        return 1;
    }
}

int FIFO_CREATE_NAME(remove)(
    struct FIFO_STRUCT_NAME *f,
    FIFO_TYPE *e)
{
    if (FIFO_CREATE_NAME(peek)(f, e) == 0)
    {
        f->out = incr(f, f->out);
        return 0;
    }
    else
    {
        return 1;
    }
}

void FIFO_CREATE_NAME(flush)(
    struct FIFO_STRUCT_NAME *f)
{
    f->out = f->in;
}

