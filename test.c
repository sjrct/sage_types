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

#include <stdio.h>
#include <assert.h>
#include "sage_types.h"

#define MAX 100

struct foo {
    SAGE_TYPE
    int a;
};

struct bar {
    SAGE_TYPE
    int b;
};

struct baz {
    SAGE_TYPE
    int c;
};

int main() {
    int i;
    struct foo *foos[MAX];
    struct bar *bars[MAX];
    struct baz *bazs[MAX];

    for (i = 0; i < MAX; i++) {
        assert(s_alloc(foos[i], struct foo));
        assert(s_alloc(bars[i], struct bar));
        assert(s_alloc(bazs[i], struct baz));
    }

    for (i = 0; i < MAX; i++) {
        assert(s_cast(foos[i], struct foo) == foos[i]);
        assert(!s_cast(foos[i], struct bar));
        assert(!s_cast(foos[i], struct baz));

        assert(!s_cast(bars[i], struct foo));
        assert(s_cast(bars[i], struct bar) == bars[i]);
        assert(!s_cast(bars[i], struct baz));

        assert(!s_cast(bazs[i], struct foo));
        assert(!s_cast(bazs[i], struct bar));
        assert(s_cast(bazs[i], struct baz) == bazs[i]);
    }

    for (i = 0; i < MAX; i++) {
        free(foos[i]);
        free(bars[i]);
        free(bazs[i]);
    }

    puts("We're all a-ok over here.");
    return 0;
}
