//
//  writer.h
//  AvidyneR9DataLoader
//
//  Created by Tim Morgan on 12/15/18.
//  Copyright © 2018 Tim Morgan. All rights reserved.
//

#ifndef writer_h
#define writer_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <csv.h>

#include "types.h"
#include "aircraft_record.h"

typedef struct _writer {
    FILE *telemetry,
    *anti_ice_systems,
    *bleed_air_systems,
    *control_surfaces,
    *displays,
    *electrical_systems,
    *engine_cylinders,
    *engine_propellers,
    *engine_spools,
    *engines,
    *flight_controls,
    *fuel_tanks,
    *hydraulic_systems,
    *ice_detection_systems,
    *instrument_sets,
    *landing_gear_tires,
    *landing_gear_trucks,
    *marker_beacons,
    *navigation_systems,
    *packs,
    *pitot_static_systems,
    *pneumatic_systems,
    *pressurization_system_valves,
    *pressurization_systems,
    *position_sensors,
    *radios,
    *radio_altimeters,
    *rotors,
    *traffic_systems,
    *transponders;
} writer;

writer *make_writer(void);
void writer_process_row(writer* const restrict writer, const aircraft_record* const restrict aircraft);
void writer_free(writer* const restrict writer);

#endif /* writer_h */
