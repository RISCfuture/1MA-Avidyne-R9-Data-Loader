//
//  transformer.c
//  AvidyneR9DataLoader
//
//  Created by Tim Morgan on 12/16/18.
//  Copyright © 2018 Tim Morgan. All rights reserved.
//

#include "transformer.h"

#define FT_TO_M(x) x.null ? x : optf(0.3048*x.i)
#define NMI_TO_M(x) x.null ? x : optf(1852*x.f)

#define MIN_TO_S(x) x.null ? x : opti(60*x.i)

#define KHZ_TO_HZ(x) x.null ? x : opti(1000*x.i)

#define F_TO_K_F(x) x.null ? x : optf((x.f - 32)*(5/9.0) + 273.15)
#define F_TO_K_I(x) x.null ? x : optf((x.i - 32)*(5/9.0) + 273.15)
#define C_TO_K(x) x.null ? x : optf(x.i + 273.15)

#define KT_TO_MPS(x) x.null ? x : optf(0.51444444444*x.i)
#define FPM_TO_MPS(x) x.null ? x : optf(0.00508*x.i)

#define GAL_TO_KL(x) x.null ? x : optf(0.00378541*x.f)

#define G_TO_MPS2(x) x.null ? x : optf(9.80665*x.f)

#define INHG_TO_PA(x) x.null ? x : optf(3386.38864034*x.f)
#define PSI_TO_PA(x) x.null ? x : optf(6894.75729317*x.i)

#define HP_TO_N(x) x.null ? x : optf(745.699871582*x.f)

#define NMI_PER_GAL_TO_M_PER_KL(x) x.null ? x : optf(489247*x.f)
#define GAL_PER_HR_TO_KL_PER_S(x) x.null ? x : optf(1.0515e-6*x.f)

#define DEG_TO_RAD(x) x.null ? x : optf(0.0174533*x.i)
#define RPM_TO_RAD_PER_S(x) x.null ? x : optf(0.10472*x.i)
#define DEG_PER_S_TO_RAD_PER_S(x) x.null ? x : optf(0.0174533*x.f)

#define HDG(x) x.null ? x : DEG_TO_RAD(opti((x.i % 360) + (x.i < 0 ? 360 : 0)))

#define ADIABATIC_INDEX_DRY_AIR 1.401
#define ISA_SEA_LEVEL_PRESSURE 101325 // Pa
#define ISA_SEA_LEVEL_TEMPERATURE 288.15 // K
#define STD_PRESSURE_LAPSE_RATE 11.1102034121 // Pa/m (1 inHg per 1000 feet)
#define STD_TEMPERATURE_LAPSE_RATE 0.0032808398950131233 // K/m
#define GAS_CONSTANT_AIR 287.058 // J/(kg K)

time_m parse_time(const csv_record* const restrict csv);

char csv_to_aircraft_adahrs(int adahrs);
char csv_to_aircraft_gps(int gps);
char csv_to_aircraft_pitot_static_system(int adahrs);

char this_ifd(const csv_record* const restrict csv);
char active_nav_system(const csv_record* const restrict csv);
char active_nav_radio(const csv_record* const restrict csv);

void calculate_sat(aircraft_record* const restrict aircraft, char adahrs);
void calculate_air_pressure(aircraft_record* const restrict aircraft, char adahrs);
void calculate_density_altitude(aircraft_record* const restrict aircraft, char adahrs);
void calculate_air_density(aircraft_record* const restrict aircraft, char adahrs);
void calculate_speed_of_sound(aircraft_record* const restrict aircraft, char adahrs);
void calculate_mach(aircraft_record* const restrict aircraft, char adahrs);
void calculate_true_heading(aircraft_record* const restrict aircraft, char sensor);
void calculate_indicated_altitude(aircraft_record* const restrict aircraft, char ifd);
void calculate_ground_elevation(aircraft_record* const restrict aircraft, char sensor);
void calculate_temperature_deviation(aircraft_record* const restrict aircraft, char sensor);

float tat_to_sat(float tat, float mach);

void csv_to_aircraft(const csv_record* const restrict csv, aircraft_record* const restrict aircraft, int csv_active_adahrs, int csv_active_gps) {
    init_aircraft_record(aircraft);

    aircraft->timestamp = parse_time(csv);

    if (!csv->system.active_wpt_id.null) {
        aircraft->navigation_systems[nav_system_fms].active_waypoint = opts_copy(csv->system.active_wpt_id);
    }

    switch (csv->flight.adahrs_used.i) {
        case 1:
            aircraft->instrument_sets[this_ifd(csv)].adahrs = optc(pos_sensor_adahrs1);
            aircraft->instrument_sets[this_ifd(csv)].pitot_static_system = optc(pitot_static_system_adahrs1);
            break;
        case 2:
            aircraft->instrument_sets[this_ifd(csv)].adahrs = optc(pos_sensor_adahrs2);
            aircraft->instrument_sets[this_ifd(csv)].pitot_static_system = optc(pitot_static_system_adahrs2);
            break;
    }
    aircraft->instrument_sets[this_ifd(csv)].altitude_bug = FT_TO_M(csv->system.alt_bug);
    aircraft->instrument_sets[this_ifd(csv)].altimeter_setting = INHG_TO_PA(csv->system.altimeter_setting);
    aircraft->autopilot_mode = opt_itoc(csv->system.autopilot_mode);
    aircraft->navigation_systems[nav_system_fms].course_deviation = HDG(csv->system.course_deviation);
    aircraft->navigation_systems[nav_system_fms].lateral_deviation = NMI_TO_M(csv->system.cross_track_deviation);
    aircraft->instrument_sets[this_ifd(csv)].cdi_source = opt_itoc(csv->system.crs_select);
    aircraft->navigation_systems[nav_system_fms].desired_track = HDG(csv->system.desired_track);
    aircraft->autopilot_altitude_target = FT_TO_M(csv->flight.dfc100_alt_target);
    aircraft->autopilot_lateral_active_mode = opt_itoc(csv->flight.dfc100_lat_active);
    aircraft->autopilot_lateral_armed_mode = opt_itoc(csv->flight.dfc100_lat_armed);
    aircraft->autopilot_vertical_active_mode = opt_itoc(csv->flight.dfc100_vert_active);
    aircraft->autopilot_vertical_armed_mode = opt_itoc(csv->flight.dfc_100_vert_armed);
    aircraft->navigation_systems[nav_system_fms].distance_to_waypoint = NMI_TO_M(csv->system.distance_to_active_wpt);
    aircraft->electrical_systems[electrical_alt1].current = csv->engine.alt1_current;
    aircraft->electrical_systems[electrical_alt2].current = csv->engine.alt2_current;
    aircraft->electrical_systems[electrical_bat2].current = csv->engine.bat2_current;
    aircraft->electrical_systems[electrical_bat1].current = csv->engine.bat_current;
    aircraft->electrical_systems[electrical_emergency_bus].potential = csv->engine.bus2_volts;
    aircraft->engines[0].cylinders[0].cylinder_head_temperature = F_TO_K_F(csv->engine.cht1);
    aircraft->engines[0].cylinders[1].cylinder_head_temperature = F_TO_K_F(csv->engine.cht2);
    aircraft->engines[0].cylinders[2].cylinder_head_temperature = F_TO_K_F(csv->engine.cht3);
    aircraft->engines[0].cylinders[3].cylinder_head_temperature = F_TO_K_F(csv->engine.cht4);
    aircraft->engines[0].cylinders[4].cylinder_head_temperature = F_TO_K_F(csv->engine.cht5);
    aircraft->engines[0].cylinders[5].cylinder_head_temperature = F_TO_K_F(csv->engine.cht6);
    aircraft->engines[0].cylinders[0].exhaust_gas_temperature = F_TO_K_F(csv->engine.egt1);
    aircraft->engines[0].cylinders[1].exhaust_gas_temperature = F_TO_K_F(csv->engine.egt2);
    aircraft->engines[0].cylinders[2].exhaust_gas_temperature = F_TO_K_F(csv->engine.egt3);
    aircraft->engines[0].cylinders[3].exhaust_gas_temperature = F_TO_K_F(csv->engine.egt4);
    aircraft->engines[0].cylinders[4].exhaust_gas_temperature = F_TO_K_F(csv->engine.egt5);
    aircraft->engines[0].cylinders[5].exhaust_gas_temperature = F_TO_K_F(csv->engine.egt6);
    aircraft->engines[0].manifold_pressure = INHG_TO_PA(csv->engine.manifold_pressure);
    aircraft->electrical_systems[electrical_main_bus].potential = csv->engine.mbus1_volts.null ? csv->engine.bus1_volts : csv->engine.mbus1_volts;
    aircraft->engines[0].oil_pressure = PSI_TO_PA(csv->engine.oil_pressure);
    aircraft->engines[0].oil_temperature = F_TO_K_I(csv->engine.oil_temperature);
    aircraft->engines[0].percent_power = csv->engine.percent_pwr;
    aircraft->engines[0].propellers[0].rotational_velocity = RPM_TO_RAD_PER_S(csv->engine.rpm);
    aircraft->engines[0].turbine_inlet_temperature = F_TO_K_I(csv->engine.tit);
    aircraft->instrument_sets[this_ifd(csv)].flight_director_active = opt_itob(csv->system.flight_director_on_off);
    aircraft->instrument_sets[this_ifd(csv)].flight_director_pitch = DEG_TO_RAD(csv->flight.flight_director_pitch);
    aircraft->instrument_sets[this_ifd(csv)].flight_director_roll = DEG_TO_RAD(csv->flight.flight_director_roll);
    aircraft->navigation_systems[nav_system_fms].course = HDG(csv->system.fms_course);
    aircraft->fuel_totalizer_economy = NMI_PER_GAL_TO_M_PER_KL(csv->engine.fuel_economy);
    aircraft->engines[0].fuel_flow = GAL_PER_HR_TO_KL_PER_S(csv->engine.fuel_flow);
    aircraft->fuel_totalizer_remaining = GAL_TO_KL(csv->engine.fuel_remaining);
    aircraft->fuel_totalizer_time_remaining = MIN_TO_S(csv->engine.fuel_time_remaining);
    aircraft->fuel_totalizer_used = GAL_TO_KL(csv->engine.fuel_used);
    aircraft->instrument_sets[this_ifd(csv)].gps = opt_itoc(csv->system.gps_select);
    aircraft->instrument_sets[nav_system_fms].heading_bug = HDG(csv->system.hdg_bug);
    aircraft->acceleration_lateral = G_TO_MPS2(csv->flight.lateral_acc);
    aircraft->acceleration_longitudinal = G_TO_MPS2(csv->flight.long_acc);
    aircraft->magnetic_variation = DEG_TO_RAD(csv->system.mag_var);
    aircraft->navigation_systems[nav_system_fms].mode = opt_itoc(csv->system.navigation_mode);
    aircraft->acceleration_normal = G_TO_MPS2(csv->flight.norm_acc);
    aircraft->instrument_sets[this_ifd(csv)].obs = HDG(csv->system.obs);
    aircraft->navigation_systems[nav_system_fms].vertical_deviation = FT_TO_M(csv->system.vertical_deviation);
    aircraft->instrument_sets[this_ifd(csv)].vertical_speed_bug = FPM_TO_MPS(csv->system.vsi_bug);

    char active_adahrs = csv_to_aircraft_adahrs(csv_active_adahrs);
    char active_gps = csv_to_aircraft_gps(csv_active_gps);
    char active_pitot_static_system = csv_to_aircraft_pitot_static_system(csv_active_adahrs);

    if (active_adahrs != -1) {
        aircraft->position_sensors[active_adahrs].pitch_rate = DEG_PER_S_TO_RAD_PER_S(csv->flight.body_pitch_rate);
        aircraft->position_sensors[active_adahrs].roll_rate = DEG_PER_S_TO_RAD_PER_S(csv->flight.body_roll_rate);
        aircraft->position_sensors[active_adahrs].yaw_rate = DEG_PER_S_TO_RAD_PER_S(csv->flight.body_yaw_rate);
        aircraft->position_sensors[active_adahrs].magnetic_heading = HDG(csv->flight.heading);
        aircraft->position_sensors[active_adahrs].heading_rate = DEG_PER_S_TO_RAD_PER_S(csv->flight.heading_rate);
        aircraft->position_sensors[active_adahrs].pitch = DEG_TO_RAD(csv->flight.pitch);
        aircraft->position_sensors[active_adahrs].roll = DEG_TO_RAD(csv->flight.roll);
    }
    if (active_gps != -1) {
        aircraft->position_sensors[active_gps].height_agl = opt_itof(csv->system.gps_agl_height);
        aircraft->position_sensors[active_gps].altitude = csv->system.gps_msl_altitude.null ? opt_itof(csv->system.gps_altitude) : opt_itof(csv->system.gps_msl_altitude);
        aircraft->position_sensors[active_gps].latitude = csv->flight.gps_latitude;
        aircraft->position_sensors[active_gps].longitude = csv->flight.gps_longitude;
        aircraft->position_sensors[active_gps].state = opt_itoc(csv->system.gps_state);
        aircraft->position_sensors[active_gps].ground_speed = KT_TO_MPS(csv->system.ground_speed);
        aircraft->position_sensors[active_gps].magnetic_track = HDG(csv->system.ground_track);
        aircraft->position_sensors[active_gps].horizontal_figure_of_merit = opt_itof(csv->system.hfom);
        aircraft->position_sensors[active_gps].horizontal_protection_level = opt_itof(csv->system.hpl_sbas);
        aircraft->position_sensors[active_gps].vertical_figure_of_merit = opt_itof(csv->system.vfom);
        aircraft->position_sensors[active_gps].vertical_protection_level = opt_itof(csv->system.vpl_sbas);

    }
    if (active_pitot_static_system != -1) {
        aircraft->pitot_static_systems[active_pitot_static_system].total_air_temperature = C_TO_K(csv->system.outside_air_temperature);
        aircraft->pitot_static_systems[active_pitot_static_system].pressure_altitude = FT_TO_M(csv->flight.pressure_altitude);
        aircraft->pitot_static_systems[active_pitot_static_system].true_airpseed = KT_TO_MPS(csv->flight.true_airspeed);
        aircraft->pitot_static_systems[active_pitot_static_system].vertical_speed = FPM_TO_MPS(csv->flight.vertical_speed);
        aircraft->pitot_static_systems[active_pitot_static_system].indicated_airspeed = KT_TO_MPS(csv->flight.indicated_airspeed);
    }

    if (active_nav_system(csv) != -1) {
        aircraft->navigation_systems[active_nav_system(csv)].vertical_deviation_factor = csv->system.glideslope_deviation;
        aircraft->navigation_systems[active_nav_system(csv)].lateral_deviation_factor = csv->system.localizer_deviation;
        aircraft->navigation_systems[active_nav_system(csv)].bearing = HDG(csv->system.navaid_brg);
        aircraft->navigation_systems[active_nav_system(csv)].mode = opt_itoc(csv->system.nav_type);
    }
    if (active_nav_radio(csv) != -1)
        aircraft->radios[active_nav_radio(csv)].active_frequency = KHZ_TO_HZ(csv->system.nav_freq);
}

time_m parse_time(const csv_record* const restrict csv) {
    const char *date, *time;
    unsigned int systime;
    if (!csv->engine.date.null && !csv->engine.time.null) {
        date = csv->engine.date.s;
        time = csv->engine.time.s;
        systime = csv->engine.systime.u;
    } else if (!csv->flight.date.null && !csv->flight.time.null) {
        date = csv->flight.date.s;
        time = csv->flight.time.s;
        systime = csv->flight.systime.u;
    } else if (!csv->system.date.null && !csv->system.time.null) {
        date = csv->system.date.s;
        time = csv->system.time.s;
        systime = csv->system.systime.u;
    }
    else {
        fprintf(stderr, "CSV record with no time information\n");
        exit(8);
    }

    char datetime[22];
    strcpy(datetime, date);
    strcat(datetime, time);
    strcat(datetime, " GMT");
    unsigned int millis = systime % 1000;

    struct tm time_obj;
    if (strptime(datetime, "%Y%m%d%H:%M:%S %Z", &time_obj)) {
        time_obj.tm_gmtoff = 0;
        time_obj.tm_isdst = -1;
        time_t time = mktime(&time_obj);
        if (time == -1) {
            fprintf(stderr, "Invalid date and time %s\n", datetime);
        }

        time_m time_plus_millis;
        time_plus_millis.seconds = time;
        time_plus_millis.milliseconds = millis;
        return time_plus_millis;
    } else {
        fprintf(stderr, "Invalid time %s\n", datetime);
        exit(6);
    }
}

char this_ifd(const csv_record* const restrict csv) {
    return csv->pilot ? instrument_set_ifd1 : instrument_set_ifd2;
}

char active_nav_system(const csv_record* const restrict csv) {
    switch (csv->system.crs_select.i) {
        case 0: return nav_system_fms;
        case 1: return nav_system_nav1;
        case 2: return nav_system_nav2;
        default: return -1;
    }
}

char active_nav_radio(const csv_record* const restrict csv) {
    switch (csv->system.crs_select.i) {
        case 1: return radio_nav1;
        case 2: return radio_nav2;
        default: return -1;
    }
}

void calculate_estimated_data(aircraft_record* const restrict aircraft) {
    if (!aircraft->engines[0].percent_power.null)
        aircraft->engines[0].power = HP_TO_N(optf(310*aircraft->engines[0].percent_power.f));

    calculate_indicated_altitude(aircraft, instrument_set_ifd1);
    calculate_indicated_altitude(aircraft, instrument_set_ifd2);

    calculate_true_heading(aircraft, pos_sensor_adahrs1);
    calculate_true_heading(aircraft, pos_sensor_adahrs2);
    calculate_true_heading(aircraft, pos_sensor_gps1);
    calculate_true_heading(aircraft, pos_sensor_gps2);

    calculate_ground_elevation(aircraft, pos_sensor_gps1);
    calculate_ground_elevation(aircraft, pos_sensor_gps2);

    calculate_air_pressure(aircraft, pitot_static_system_adahrs1);
    calculate_air_pressure(aircraft, pitot_static_system_adahrs2);

    calculate_air_density(aircraft, pitot_static_system_adahrs1);
    calculate_air_density(aircraft, pitot_static_system_adahrs2);

    calculate_density_altitude(aircraft, pitot_static_system_adahrs1);
    calculate_density_altitude(aircraft, pitot_static_system_adahrs2);

    calculate_speed_of_sound(aircraft, pitot_static_system_adahrs1);
    calculate_speed_of_sound(aircraft, pitot_static_system_adahrs2);

    calculate_mach(aircraft, pitot_static_system_adahrs1);
    calculate_mach(aircraft, pitot_static_system_adahrs2);

    calculate_sat(aircraft, pitot_static_system_adahrs1);
    calculate_sat(aircraft, pitot_static_system_adahrs2);

    calculate_temperature_deviation(aircraft, pitot_static_system_adahrs1);
    calculate_temperature_deviation(aircraft, pitot_static_system_adahrs2);
}

// exact
void calculate_indicated_altitude(aircraft_record* const restrict aircraft, char ifd) {
    optional adahrs = aircraft->instrument_sets[ifd].adahrs;
    if (adahrs.null) return;
    optional pressure_altitude = aircraft->pitot_static_systems[adahrs.c].pressure_altitude;
    if (pressure_altitude.null) return;
    optional altimeter_setting = aircraft->instrument_sets[ifd].altimeter_setting;
    if (altimeter_setting.null) return;

    float indicated_altitude = pressure_altitude.f + (altimeter_setting.f - ISA_SEA_LEVEL_PRESSURE)/STD_PRESSURE_LAPSE_RATE;
    aircraft->instrument_sets[ifd].indicated_altitude = optf(indicated_altitude);
}

// exact
void calculate_true_heading(aircraft_record* const restrict aircraft, char sensor) {
    if (aircraft->magnetic_variation.null) return;

    if (!aircraft->position_sensors[sensor].magnetic_heading.null)
        aircraft->position_sensors[sensor].true_heading = optf(aircraft->position_sensors[sensor].magnetic_heading.f - aircraft->magnetic_variation.f);

    if (!aircraft->position_sensors[sensor].magnetic_track.null)
        aircraft->position_sensors[sensor].true_track = optf(aircraft->position_sensors[sensor].magnetic_track.f - aircraft->magnetic_variation.f);
}

// exact
void calculate_ground_elevation(aircraft_record* const restrict aircraft, char sensor) {
    optional msl = aircraft->position_sensors[sensor].altitude;
    if (msl.null) return;
    optional agl = aircraft->position_sensors[sensor].height_agl;
    if (agl.null) return;

    aircraft->position_sensors[sensor].ground_elevation = optf(msl.f - agl.f);
}

// assumes ISA pressure lapse rate
void calculate_air_pressure(aircraft_record* const restrict aircraft, char adahrs) {
    optional pressure_altitude = aircraft->pitot_static_systems[adahrs].pressure_altitude;
    if (pressure_altitude.null) return;

    aircraft->pitot_static_systems[adahrs].air_pressure = optf(ISA_SEA_LEVEL_PRESSURE-pressure_altitude.f*STD_PRESSURE_LAPSE_RATE);
}

// assumes ISA pressure lapse rate
// uses TAT in place of SAT
// assumes ISA humidity
void calculate_air_density(aircraft_record* const restrict aircraft, char adahrs) {
    optional air_pressure = aircraft->pitot_static_systems[adahrs].air_pressure;
    if (air_pressure.null) return;
    optional static_air_temperature = aircraft->pitot_static_systems[adahrs].total_air_temperature;
    if (static_air_temperature.null) return;

    aircraft->pitot_static_systems[adahrs].air_density = optf(air_pressure.f/(GAS_CONSTANT_AIR*static_air_temperature.f));
}

// assumes ISA pressure lapse rate
// uses TAT in place of SAT
// assumes ISA humidity
void calculate_density_altitude(aircraft_record* const restrict aircraft, char adahrs) {
    optional air_density = aircraft->pitot_static_systems[adahrs].air_density;
    if (air_density.null) return;

    aircraft->pitot_static_systems[adahrs].density_altitude = optf(43911.917098445585 - 41843.6951063124*pow(air_density.f, 0.23774838365003717));
}

// assumes ISA pressure lapse rate
// uses TAT in place of SAT
// assumes ISA humidity
void calculate_speed_of_sound(aircraft_record* const restrict aircraft, char adahrs) {
    if (aircraft->pitot_static_systems[adahrs].air_pressure.null) return;
    if (aircraft->pitot_static_systems[adahrs].air_density.null) return;

    aircraft->pitot_static_systems[adahrs].speed_of_sound = optf(sqrtf(ADIABATIC_INDEX_DRY_AIR*aircraft->pitot_static_systems[adahrs].air_pressure.f/aircraft->pitot_static_systems[adahrs].air_density.f));
}

// assumes ISA pressure lapse rate
// uses TAT in place of SAT
// assumes ISA humidity
void calculate_mach(aircraft_record* const restrict aircraft, char adahrs) {
    if (aircraft->pitot_static_systems[adahrs].speed_of_sound.null) return;
    if (aircraft->pitot_static_systems[adahrs].true_airpseed.null) return;

    aircraft->pitot_static_systems[adahrs].mach = optf(aircraft->pitot_static_systems[adahrs].true_airpseed.f / aircraft->pitot_static_systems[adahrs].speed_of_sound.f);
}

// assumes ISA pressure lapse rate
// assumes ISA humidity
void calculate_sat(aircraft_record* const restrict aircraft, char adahrs) {
    if (aircraft->pitot_static_systems[adahrs].total_air_temperature.null) return;
    if (aircraft->pitot_static_systems[adahrs].mach.null) return;

    aircraft->pitot_static_systems[adahrs].static_air_temperature = optf(tat_to_sat(aircraft->pitot_static_systems[adahrs].total_air_temperature.f, aircraft->pitot_static_systems[adahrs].mach.f));
}

float tat_to_sat(float tat, float mach) {
    float ram_rise = 1 + (ADIABATIC_INDEX_DRY_AIR - 1)/2 * powf(mach, 2);
    return tat/ram_rise;
}

// valid in troposphere only
void calculate_temperature_deviation(aircraft_record* const restrict aircraft, char sensor) {
    if (aircraft->pitot_static_systems[sensor].static_air_temperature.null) return;
    if (aircraft->pitot_static_systems[sensor].pressure_altitude.null) return;

    float standard_temperature = ISA_SEA_LEVEL_TEMPERATURE - aircraft->pitot_static_systems[sensor].pressure_altitude.f*STD_TEMPERATURE_LAPSE_RATE;
    aircraft->pitot_static_systems[sensor].temperature_deviation = optf(aircraft->pitot_static_systems[sensor].static_air_temperature.f - standard_temperature);
}

char csv_to_aircraft_adahrs(int adahrs) {
    switch (adahrs) {
        case 1: return pos_sensor_adahrs1;
        case 2: return pos_sensor_adahrs2;
        default: return -1;
    }
}

char csv_to_aircraft_gps(int gps) {
    switch (gps) {
        case 1: return pos_sensor_gps1;
        case 2: return pos_sensor_gps2;
        default: return -1;
    }
}

char csv_to_aircraft_pitot_static_system(int adahrs) {
    switch (adahrs) {
        case 1: return pitot_static_system_adahrs1;
        case 2: return pitot_static_system_adahrs2;
        default: return -1;
    }
}
