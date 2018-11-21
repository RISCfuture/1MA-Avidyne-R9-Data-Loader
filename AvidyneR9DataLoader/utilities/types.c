//
//  types.c
//  AvidyneR9DataLoader
//
//  Created by Tim Morgan on 1/15/19.
//  Copyright © 2019 Tim Morgan. All rights reserved.
//

#include "types.h"

optional optnull(void) {
    optional o;
    o.null = true;
    return o;
}

optional opti(int i) {
    optional o;
    o.i = i;
    o.null = false;
    return o;
}

optional optu(unsigned int i) {
    optional o;
    o.i = i;
    o.null = false;
    return o;
}

optional optf(float f) {
    optional o;
    o.f = f;
    o.null = false;
    return o;
}

optional optt(time_t t) {
    optional o;
    o.t = t;
    o.null = false;
    return o;
}

optional opts(const char* const s) {
    optional o;
    o.s = s;
    o.null = false;
    return o;
}

optional optb(bool b) {
    optional o;
    o.b = b;
    o.null = false;
    return o;
}

optional optc(char c) {
    optional o;
    o.c = c;
    o.null = false;
    return o;
}

optional optsh(short s) {
    optional o;
    o.sh = s;
    o.null = false;
    return o;
}

optional opts_copy(const optional o) {
    if (o.null) return o;

    optional new;
    new.s = malloc(sizeof(char)*(strlen(o.s) + 1));
    strcpy(new.s, o.s);
    new.null = false;
    return new;
}

optional opt_itob(optional i) {
    if (i.null) return i;
    return optb(i.i);
}

optional opt_itoc(optional i) {
    if (i.null) return i;
    return optc(i.i);
}

optional opt_itosh(optional i) {
    if (i.null) return i;
    return optsh(i.i);
}

optional opt_itof(optional i) {
    if (i.null) return i;
    return optf(i.i);
}

