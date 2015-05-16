/**
 * The MIT License (MIT)
 *
 * Copyright (c) 2015 Chris Harding
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

/**
 * Usage:
 *
 * Inside of a struct for which you want to use safe casting, place the string
 * "SAGE_TYPE". Then, whenever you allocate an instance of that struct use the
 * "s_alloc" macro, and whenever you cast to that struct use the "s_cast" macro,
 * being sure to check the return value.
 *
 * The s_cast macro requires access to the struct's fields, so out-of-the-box
 * sage types cannot be used to cast opaque structures. You can get around this
 * by defining the macro SAGE_USE_OFFSET_0. If you define this make sure that
 * in your sage structs you have "SAGE_TYPE" as the FIRST thing in your struct,
 * otherwise things will not behave as expected.
 *
 * You can turn off type checking if you want for release builds and the like by
 * defining the NO_SAGE_TYPES macro.
 */

#ifndef SAGE_TYPES_H
#define SAGE_TYPES_H

#include <stdlib.h>
#include <string.h>

#ifndef NO_SAGE_TYPES

#ifdef SAGE_USE_OFFSET_0
#  define _SAGE_GET_MARKER(P) ( *(const char **) (P) )
#else
#  define _SAGE_GET_MARKER(P) ( (P)->_sage_marker )
#endif

/**
 * Place inside your struct's declaration.
 */
#define SAGE_TYPE \
    const char *_sage_marker;

/**
 * Use "s_alloc(foo, bar_t)" instead of "foo = malloc(sizeof(bar_t))"
 *
 * Returns "1" if successful, "0" if not. (i.e. if malloc returns NULL)
 */
#define s_alloc(DEST, TYPE) \
    ( \
        (DEST = (TYPE *)malloc(sizeof(TYPE))) && \
        ( (_SAGE_GET_MARKER(DEST) = #TYPE) || 1 ) \
    )

/**
 * Use "s_cast(bar_t, foo)" instead of "(bar_t *) foo"
 *
 * Returns casted pointer if successful, NULL if not the right type
 */
#define s_cast(FROM, TYPE) \
    ( \
        ( strcmp(_SAGE_GET_MARKER(FROM), #TYPE) ) \
        ? NULL \
        : ( (TYPE *) FROM ) \
    )

#else /* NO_SAGE_TYPES */

#define SAGE_TYPE_DECLARE(_)
#define SAGE_TYPE

#define s_alloc(DEST, TYPE) \
    ( (DEST = malloc(sizeof(TYPE))) || 1 )

#define s_cast(FROM, TYPE) \
    ( (TYPE *) FROM )

#endif /* NO_SAGE_TYPES */

#endif /* SAGE_TYPES_H */
