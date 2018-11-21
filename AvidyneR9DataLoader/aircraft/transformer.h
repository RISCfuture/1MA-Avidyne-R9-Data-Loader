//
//  transformer.h
//  AvidyneR9DataLoader
//
//  Created by Tim Morgan on 12/16/18.
//  Copyright © 2018 Tim Morgan. All rights reserved.
//

#ifndef transformer_h
#define transformer_h

#include <math.h>
#include <string.h>

#include "types.h"
#include "time.h"
#include "csv_record.h"
#include "aircraft_record.h"

enum {
    radio_comm1 = 0,
    radio_comm2,
    radio_nav1,
    radio_nav2
};

enum {
    pos_sensor_adahrs1 = 0,
    pos_sensor_adahrs2,
    pos_sensor_gps1,
    pos_sensor_gps2
};

enum {
    nav_system_fms = 0,
    nav_system_nav1,
    nav_system_nav2
};

enum {
    instrument_set_ifd1 = 0,
    instrument_set_ifd2
};

enum {
    pitot_static_system_adahrs1 = 0,
    pitot_static_system_adahrs2
};

enum {
    electrical_bat1 = 0,
    electrical_bat2,
    electrical_alt1,
    electrical_alt2,
    electrical_main_bus,
    electrical_emergency_bus
};

void csv_to_aircraft(const csv_record* const restrict csv, aircraft_record* const restrict aircraft, int active_adahrs, int active_gps);
void calculate_estimated_data(aircraft_record* const restrict aircraft);

#endif /* transformer_h */
