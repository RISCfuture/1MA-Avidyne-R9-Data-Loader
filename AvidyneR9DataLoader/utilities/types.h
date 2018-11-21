//
//  types.h
//  AvidyneR9DataLoader
//
//  Created by Tim Morgan on 1/15/19.
//  Copyright © 2019 Tim Morgan. All rights reserved.
//

#ifndef types_h
#define types_h

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "time.h"

typedef struct _optional {
    bool null;
    union {
        float f;
        int i;
        unsigned int u;
        time_t t;
        char *s;
        bool b;
        char c;
        short sh;
    };
} optional;

#endif /* types_h */

optional optnull(void);
optional opti(int i);
optional optu(unsigned int i);
optional optf(float f);
optional optt(time_t t);
optional opts(const char* const s);
optional optb(bool b);
optional optc(char c);
optional optsh(short s);

optional opts_copy(const optional o);

optional opt_itob(optional i);
optional opt_itoc(optional i);
optional opt_itosh(optional i);
optional opt_itof(optional i);
