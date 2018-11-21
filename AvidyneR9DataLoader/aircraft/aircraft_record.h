//
//  database_record.h
//  AvidyneR9DataLoader
//
//  Created by Tim Morgan on 12/16/18.
//  Copyright © 2018 Tim Morgan. All rights reserved.
//

#ifndef database_record_h
#define database_record_h

#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "types.h"

typedef struct _aircraft {
    unsigned int id;
    unsigned char num_anti_ice_systems, num_bleed_air_systems, num_control_surfaces, num_displays, num_electrical_systems, num_engines, num_fuel_tanks, num_hydraulic_systems, num_ice_detection_systems, num_instrument_sets, num_trucks, num_marker_beacons, num_navigation_systems, num_packs, num_pitot_static_systems, num_pneumatic_systems, num_position_sensors, num_pressurization_systems, num_radios, num_radio_altimeters, num_rotors, num_transponders, num_traffic_systems, num_flight_control_sets, num_flight_controls;
    unsigned char cylinders_per_engine[256];
    unsigned char propellers_per_engine[256];
    unsigned char spools_per_engine[256];
    unsigned char tires_per_truck[256];
    unsigned char valves_per_pressurization_system[256];
} aircraft;

typedef struct _anti_ice_system {
    optional active,
        mode,

        current,
        fluid_quantity, fluid_flow_rate,
        vacuum;
} anti_ice_system;

typedef struct _bleed_air_system {
    optional active,
        temperature, pressure,
        valve_position;
} bleed_air_system;

typedef struct _control_surface {
    optional position, trim,
        position_factor, trim_factor;
} control_surface;

typedef struct _display {
    optional active, format;
} display;

typedef struct _electrical_system {
    optional active,
        current, potential, frequency;
} electrical_system;

typedef struct _cylinder {
    optional cylinder_head_temperature, exhaust_gas_temperature;
} cylinder;

typedef struct _propeller {
    optional rotational_velocity;
} propeller;

typedef struct _spool {
    optional n, rotational_velocity;
} spool;

typedef struct _valve {
    optional position;
} valve;


typedef struct _engine {
    optional fuel_flow, fuel_pressure,
        vibration,

        thrust_lever_position, reverser_position, reverser_lever_stowed, throttle_position, mixture_lever_position, propeller_lever_position,
        magneto_position,
        carburetor_heat_lever_position, cowl_flap_lever_position, altitude_throttle_position, condition_lever_position, beta_position,

        ignition_mode,
        autothrottle_active,

        fuel_source,

        reverser_opened,

        torque, torque_factor,
        autofeather_armed,

        manifold_pressure,

        thrust, percent_thrust,
        power, percent_power,
        engine_pressure_ratio,

        exhaust_gas_temperature, interstage_turbine_temperature, turbine_inlet_temperature,

        oil_pressure, oil_temperature;

    cylinder *cylinders;
    spool *spools;
    propeller *propellers;
} engine;

typedef struct _flight_control {
    optional position,
        shaker, pusher;
} flight_control;

typedef struct _fuel_tank {
    optional quantity, quantity_weight,
        temperature;
} fuel_tank;

typedef struct _hydraulic_system {
    optional pressure, temperature,
        fluid_quantity, fluid_quantity_percent;
} hydraulic_system;

typedef struct _ice_detection_system {
    optional ice_detected;
} ice_detection_system;

typedef struct _instrument_set {
    optional flight_director, ins, gps, adahrs, fms, nav_radio, adf, pitot_static_system, cdi_source,

        obs, course,
        altitude_bug, decision_height, indicated_airspeed_bug, mach_bug, vertical_speed_bug, flight_path_angle_bug,
        heading_bug, track_bug,

        indicated_altitude, altimeter_setting,

        flight_director_active,
        flight_director_pitch, flight_director_roll;
} instrument_set;

typedef struct _tire {
    optional brake_temperature, air_pressure;
} tire;

typedef struct _truck {
    optional door_state, weight_on_wheels;
    tire *tires;
} truck;

typedef struct _marker_beacon {
    optional outer, middle, inner;
} marker_beacon;

typedef struct _navigation_system {
    optional active,
        mode,

        desired_track, course, bearing,

        course_deviation,
        lateral_deviation, vertical_deviation,
        lateral_deviation_factor, vertical_deviation_factor,

        active_waypoint,
        distance_to_waypoint,

        radio;
} navigation_system;

typedef struct _pack {
    optional active,
        air_pressure, air_temperature;
} pack;

typedef struct _pitot_static_system {
    optional static_air_temperature, total_air_temperature, temperature_deviation,
        air_pressure, air_density,
        pressure_altitude, density_altitude,

        indicated_airspeed, calibrated_airspeed, true_airpseed,
        speed_of_sound, mach,

        vertical_speed,

        angle_of_attack, angle_of_sideslip;
} pitot_static_system;

typedef struct _pneumatic_system {
    optional pressure;
} pneumatic_system;

typedef struct _pressurization_system {
    optional mode,
    differential_pressure,
    cabin_altitude, cabin_rate, target_altitude;

    valve *valves;
} pressurization_system;

typedef struct _position_sensor {
    optional state,

        roll, pitch,
        true_heading, magnetic_heading, grid_heading,
        true_track, magnetic_track, grid_track,

        longitude, latitude, altitude,
        ground_elevation, height_agl,

        pitch_rate, roll_rate, yaw_rate, heading_rate,

        ground_speed, vertical_speed,
        climb_gradient, climb_angle,

        horizontal_figure_of_merit, vertical_figure_of_merit, horizontal_protection_level, vertical_protection_level;
} position_sensor;

typedef struct _radio {
    optional active, monitoring, monitoring_standby,
        transmitting, receiving, squelched,
        beat_frequency_oscillation, ident, single_sideband,
        active_frequency, standby_frequency,
        volume, squelch;
} radio;

typedef struct _radio_altimeter {
    optional state,
        altitude, alert_altitude;
} radio_altimeter;

typedef struct _rotor {
    optional rotational_velocity,
        blade_angle;
} rotor;

typedef struct _transponder {
    optional mode,
        mode_3a_code, mode_s_code, flight_id,
        replying;
} transponder;

typedef struct _traffic_system {
    optional mode,
        traffic_advisory, resolution_advisory,
        horizontal_resolution_advisory, vertical_resolution_advisory;
} traffic_system;

typedef struct _aircraft_record {
    aircraft *aircraft;
    time_m timestamp;

    optional acceleration_lateral, acceleration_longitudinal, acceleration_normal,

        magnetic_variation, grid_convergence,

        fuel_totalizer_used, fuel_totalizer_remaining, fuel_totalizer_economy,
        fuel_totalizer_used_weight, fuel_totalizer_remaining_weight, fuel_totalizer_economy_weight,
        fuel_totalizer_time_remaining,

        autopilot_active,
        autopilot_mode, autopilot_lateral_active_mode, autopilot_lateral_armed_mode, autopilot_vertical_active_mode, autopilot_vertical_armed_mode,
        autopilot_altitude_target,
        autothrottle_active_mode, autothrottle_armed_mode,

        master_warning, master_caution, fire_warning,

        drift_angle, wind_direction, wind_speed,

        mass, center_of_gravity, percent_mac;

    anti_ice_system *anti_ice_systems;
    bleed_air_system *bleed_air_systems;
    control_surface *control_surfaces;
    display *displays;
    electrical_system *electrical_systems;
    engine *engines;
    flight_control **flight_controls;
    fuel_tank *fuel_tanks;
    hydraulic_system *hydraulic_systems;
    ice_detection_system *ice_detection_systems;
    instrument_set *instrument_sets;
    truck *trucks;
    marker_beacon *marker_beacons;
    navigation_system *navigation_systems;
    pack *packs;
    pitot_static_system *pitot_static_systems;
    pneumatic_system *pneumatic_systems;
    pressurization_system *pressurization_systems;
    position_sensor *position_sensors;
    radio *radios;
    radio_altimeter *radio_altimeters;
    rotor *rotors;
    transponder *transponders;
    traffic_system *traffic_systems;
} aircraft_record;

aircraft_record *make_aircraft_record(aircraft* const aircraft);
void init_aircraft_record(aircraft_record* const restrict record);
void aircraft_record_free(aircraft_record* const restrict record);

void aircraft_record_merge(aircraft_record* const restrict predator, const aircraft_record* const restrict prey);

#endif /* database_record_h */
