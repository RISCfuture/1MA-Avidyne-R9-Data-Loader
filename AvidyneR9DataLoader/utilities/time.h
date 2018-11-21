//
//  time.h
//  AvidyneR9DataLoader
//
//  Created by Tim Morgan on 5/8/19.
//  Copyright © 2019 Tim Morgan. All rights reserved.
//

#ifndef time_h
#define time_h

#include <time.h>

typedef struct _time_m {
    time_t seconds;
    unsigned short milliseconds;
} time_m;

typedef struct _calendar_m {
    struct tm calendar;
    unsigned short milliseconds;
} calendar_m;

#endif /* time_h */
