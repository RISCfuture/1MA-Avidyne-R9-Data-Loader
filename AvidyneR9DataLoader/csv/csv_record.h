//
//  record.h
//  AvidyneR9DataLoader
//
//  Created by Tim Morgan on 11/21/18.
//  Copyright © 2018 Tim Morgan. All rights reserved.
//

#ifndef record_h
#define record_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "types.h"

typedef struct _flight_record {
    optional systime,
        date, time,

        norm_acc, long_acc, lateral_acc,

        adahrs_used,
        ahrs_status_bits,

        heading, pitch, roll,
        flight_director_pitch, flight_director_roll,
        heading_rate,

        pressure_altitude,
        indicated_airspeed, true_airspeed, vertical_speed,

        gps_latitude, gps_longitude,

        body_yaw_rate, body_pitch_rate, body_roll_rate,

        mag_status, iru_status, mpu_status, adc_status,
        ahrs_seq, adc_seq, ahrs_startup_mode,

        dfc100_lat_active, dfc100_lat_armed, dfc100_vert_active, dfc_100_vert_armed,
        dfc100_status_flags, dfc_100_fail_flags,
        dfc100_alt_target;

} flight_record;

typedef struct _system_record {
    optional systime,
        date, time,

        outside_air_temperature,

        localizer_deviation, glideslope_deviation,

        flight_director_on_off,
        autopilot_mode,

        ground_speed,

        ground_track,
        cross_track_deviation,
        vertical_deviation,

        altimeter_setting,
        alt_bug, vsi_bug, hdg_bug,

        display_mode, navigation_mode,
        active_wpt_id,
        gps_select,

        navaid_brg, obs, desired_track,
        nav_freq,
        crs_select, nav_type, course_deviation,

        gps_altitude,
        distance_to_active_wpt,

        gps_state,
        gps_horiz_prot_limit, gps_vert_prot_limit,
        hpl_sbas, vpl_sbas,
        hfom, vfom,

        fms_course,
        mag_var,

        gps_msl_altitude, gps_agl_height,

        flta_rtc, flta_atc, flta_vspd, flta_rtc_dist, flta_terr_dist, flta_status;
} system_record;

typedef struct _engine_record {
    optional systime,
        date, time,

        oil_temperature, oil_pressure,
        rpm,
        manifold_pressure,
        tit,

        cht1, cht2, cht3, cht4, cht5, cht6,
        egt1, egt2, egt3, egt4, egt5, egt6,

        percent_pwr,
        fuel_flow,
        fuel_used, fuel_remaining,
        fuel_time_remaining,
        fuel_economy,

        alt1_current, alt2_current, bat_current, bat2_current,
        mbus1_volts, mbus2_volts,
        bus1_volts, bus2_volts, bus3_volts,

        discrete_inputs, discrete_outputs,

        l_fuel_qty, r_fuel_qty,

        deice_vac,
        rudder_trim,
        flaps,
        ng,
        torque, itt, np;
} engine_record;

typedef enum _record_type {
    record_flight = 1,
    record_system,
    record_engine
} record_type;

typedef struct _csv_record {
    bool pilot;
    bool legacy;

    flight_record flight;
    system_record system;
    engine_record engine;
} csv_record;

csv_record *make_csv_record(void);
void csv_record_free(csv_record* const restrict row);

#endif /* record_h */
