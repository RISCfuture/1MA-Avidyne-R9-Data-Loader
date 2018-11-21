//
//  writer.c
//  AvidyneR9DataLoader
//
//  Created by Tim Morgan on 12/15/18.
//  Copyright © 2018 Tim Morgan. All rights reserved.
//

#include "writer.h"

void write_telemetry(FILE* const restrict file, const aircraft_record* const restrict aircraft);
void write_anti_ice_systems(FILE* const restrict file, const aircraft_record* const restrict aircraft);
void write_bleed_air_systems(FILE* const restrict file, const aircraft_record* const restrict aircraft);
void write_control_surfaces(FILE* const restrict file, const aircraft_record* const restrict aircraft);
void write_displays(FILE* const restrict file, const aircraft_record* const restrict aircraft);
void write_electrical_systems(FILE* const restrict file, const aircraft_record* const restrict aircraft);
void write_engine_cylinders(FILE* const restrict file, const aircraft_record* const restrict aircraft);
void write_engine_propellers(FILE* const restrict file, const aircraft_record* const restrict aircraft);
void write_engine_spools(FILE* const restrict file, const aircraft_record* const restrict aircraft);
void write_engines(FILE* const restrict file, const aircraft_record* const restrict aircraft);
void write_flight_controls(FILE* const restrict file, const aircraft_record* const restrict aircraft);
void write_fuel_tanks(FILE* const restrict file, const aircraft_record* const restrict aircraft);
void write_ice_detection_systems(FILE* const restrict file, const aircraft_record* const restrict aircraft);
void write_hydraulic_systems(FILE* const restrict file, const aircraft_record* const restrict aircraft);
void write_instrument_sets(FILE* const restrict file, const aircraft_record* const restrict aircraft);
void write_landing_gear_tires(FILE* const restrict file, const aircraft_record* const restrict aircraft);
void write_landing_gear_trucks(FILE* const restrict file, const aircraft_record* const restrict aircraft);
void write_marker_beacons(FILE* const restrict file, const aircraft_record* const restrict aircraft);
void write_navigation_systems(FILE* const restrict file, const aircraft_record* const restrict aircraft);
void write_packs(FILE* const restrict file, const aircraft_record* const restrict aircraft);
void write_pitot_static_systems(FILE* const restrict file, const aircraft_record* const restrict aircraft);
void write_pneumatic_systems(FILE* const restrict file, const aircraft_record* const restrict aircraft);
void write_pressurization_system_valves(FILE* const restrict file, const aircraft_record* const restrict aircraft);
void write_pressurization_systems(FILE* const restrict file, const aircraft_record* const restrict aircraft);
void write_position_sensors(FILE* const restrict file, const aircraft_record* const restrict aircraft);
void write_radios(FILE* const restrict file, const aircraft_record* const restrict aircraft);
void write_radio_altimeters(FILE* const restrict file, const aircraft_record* const restrict aircraft);
void write_rotors(FILE* const restrict file, const aircraft_record* const restrict aircraft);
void write_traffic_systems(FILE* const restrict file, const aircraft_record* const restrict aircraft);
void write_transponders(FILE* const restrict file, const aircraft_record* const restrict aircraft);

void write_enum(FILE* const restrict file, optional value, bool end);
void write_int(FILE* const restrict file, optional value, bool end);
void write_raw_unsigned_int(FILE* const restrict file, unsigned int value, bool end);
void write_float(FILE* const restrict file, optional value, bool end);
void write_bool(FILE* const restrict file, optional value, bool end);
void write_timestamp(FILE* const restrict file, time_m value, bool end);
void write_string(FILE* const restrict file, optional value, bool end);
void write_position(FILE* const restrict file, optional x, optional y, optional z, bool end);
void write_null(FILE* const restrict file, bool end);
void write_raw(FILE* const restrict file, char *value, bool end);

writer *make_writer(void) {
    writer *w = malloc(sizeof(writer));

    w->telemetry = fopen("telemetry.tsv", "wb");
    w->anti_ice_systems = fopen("telemetry_anti_ice_systems.tsv", "wb");
    w->bleed_air_systems = fopen("telemetry_bleed_air_systems.tsv", "wb");
    w->control_surfaces = fopen("telemetry_control_surfaces.tsv", "wb");
    w->displays = fopen("telemetry_displays.tsv", "wb");
    w->electrical_systems = fopen("telemetry_electrical_systems.tsv", "wb");
    w->engines = fopen("telemetry_engines.tsv", "wb");
    w->engine_cylinders = fopen("telemetry_engine_cylinders.tsv", "wb");
    w->engine_propellers = fopen("telemetry_engine_propellers.tsv", "wb");
    w->engine_spools = fopen("telemetry_engine_spools.tsv", "wb");
    w->flight_controls = fopen("telemetry_flight_controls.tsv", "wb");
    w->fuel_tanks = fopen("telemetry_fuel_tanks.tsv", "wb");
    w->ice_detection_systems = fopen("telemetry_ice_detection_systems.tsv", "wb");
    w->hydraulic_systems = fopen("telemetry_hydraulic_systems.tsv", "wb");
    w->instrument_sets = fopen("telemetry_instrument_sets.tsv", "wb");
    w->landing_gear_tires = fopen("telemetry_landing_gear_tires.tsv", "wb");
    w->landing_gear_trucks = fopen("telemetry_landing_gear_trucks.tsv", "wb");
    w->marker_beacons = fopen("telemetry_marker_beacons.tsv", "wb");
    w->navigation_systems = fopen("telemetry_navigation_systems.tsv", "wb");
    w->packs = fopen("telemetry_packs.tsv", "wb");
    w->pitot_static_systems = fopen("telemetry_pitot_static_systems.tsv", "wb");
    w->pneumatic_systems = fopen("telemetry_pneumatic_systems.tsv", "wb");
    w->pressurization_system_valves = fopen("telemetry_pressurization_system_valves.tsv", "wb");
    w->pressurization_systems = fopen("telemetry_pressurization_system_valves.tsv", "wb");
    w->position_sensors = fopen("telemetry_position_sensors.tsv", "wb");
    w->radios = fopen("telemetry_radios.tsv", "wb");
    w->radio_altimeters = fopen("telemetry_radio_altimeters.tsv", "wb");
    w->rotors = fopen("telemetry_rotors.tsv", "wb");
    w->traffic_systems = fopen("telemetry_traffic_systems.tsv", "wb");
    w->transponders = fopen("telemetry_transponders.tsv", "wb");

    return w;
}

void writer_process_row(writer* const restrict writer, const aircraft_record* const restrict aircraft) {
    write_telemetry(writer->telemetry, aircraft);
    write_anti_ice_systems(writer->anti_ice_systems, aircraft);
    write_bleed_air_systems(writer->bleed_air_systems, aircraft);
    write_control_surfaces(writer->control_surfaces, aircraft);
    write_displays(writer->displays, aircraft);
    write_electrical_systems(writer->electrical_systems, aircraft);
    write_engines(writer->engines, aircraft);
    write_engine_cylinders(writer->engine_cylinders, aircraft);
    write_engine_propellers(writer->engine_propellers, aircraft);
    write_engine_spools(writer->engine_spools, aircraft);
    write_flight_controls(writer->flight_controls, aircraft);
    write_fuel_tanks(writer->fuel_tanks, aircraft);
    write_hydraulic_systems(writer->hydraulic_systems, aircraft);
    write_ice_detection_systems(writer->ice_detection_systems, aircraft);
    write_instrument_sets(writer->instrument_sets, aircraft);
    write_landing_gear_tires(writer->landing_gear_tires, aircraft);
    write_landing_gear_trucks(writer->landing_gear_trucks, aircraft);
    write_marker_beacons(writer->marker_beacons, aircraft);
    write_navigation_systems(writer->navigation_systems, aircraft);
    write_packs(writer->packs, aircraft);
    write_pitot_static_systems(writer->pitot_static_systems, aircraft);
    write_pneumatic_systems(writer->pneumatic_systems, aircraft);
    write_pressurization_system_valves(writer->pressurization_system_valves, aircraft);
    write_pressurization_systems(writer->pressurization_systems, aircraft);
    write_position_sensors(writer->position_sensors, aircraft);
    write_radios(writer->radios, aircraft);
    write_radio_altimeters(writer->radio_altimeters, aircraft);
    write_rotors(writer->rotors, aircraft);
    write_traffic_systems(writer->traffic_systems, aircraft);
    write_transponders(writer->transponders, aircraft);
}

void write_telemetry(FILE* const restrict file, const aircraft_record* const restrict aircraft) {
  if (aircraft->acceleration_lateral.null &&
      aircraft->acceleration_longitudinal.null &&
      aircraft->acceleration_normal.null &&
      aircraft->magnetic_variation.null &&
      aircraft->grid_convergence.null &&
      aircraft->fuel_totalizer_used.null &&
      aircraft->fuel_totalizer_remaining.null &&
      aircraft->fuel_totalizer_economy.null &&
      aircraft->fuel_totalizer_used_weight.null &&
      aircraft->fuel_totalizer_remaining_weight.null &&
      aircraft->fuel_totalizer_economy_weight.null &&
      aircraft->fuel_totalizer_time_remaining.null &&
      aircraft->autopilot_active.null &&
      aircraft->autopilot_mode.null &&
      aircraft->autopilot_lateral_active_mode.null &&
      aircraft->autopilot_lateral_armed_mode.null &&
      aircraft->autopilot_vertical_active_mode.null &&
      aircraft->autopilot_vertical_armed_mode.null &&
      aircraft->autopilot_altitude_target.null &&
      aircraft->autothrottle_active_mode.null &&
      aircraft->autothrottle_armed_mode.null)
      return;

    write_raw_unsigned_int(file, aircraft->aircraft->id, false);
    write_timestamp(file, aircraft->timestamp, false);
    write_float(file, aircraft->acceleration_lateral, false);
    write_float(file, aircraft->acceleration_longitudinal, false);
    write_float(file, aircraft->acceleration_normal, false);
    write_float(file, aircraft->magnetic_variation, false);
    write_float(file, aircraft->grid_convergence, false);
    write_float(file, aircraft->fuel_totalizer_used, false);
    write_float(file, aircraft->fuel_totalizer_remaining, false);
    write_float(file, aircraft->fuel_totalizer_economy, false);
    write_float(file, aircraft->fuel_totalizer_used_weight, false);
    write_float(file, aircraft->fuel_totalizer_remaining_weight, false);
    write_float(file, aircraft->fuel_totalizer_economy_weight, false);
    write_int(file, aircraft->fuel_totalizer_time_remaining, false);
    write_bool(file, aircraft->autopilot_active, false);
    write_enum(file, aircraft->autopilot_mode, false);
    write_enum(file, aircraft->autopilot_lateral_active_mode, false);
    write_enum(file, aircraft->autopilot_lateral_armed_mode, false);
    write_enum(file, aircraft->autopilot_vertical_active_mode, false);
    write_enum(file, aircraft->autopilot_vertical_armed_mode, false);
    write_float(file, aircraft->autopilot_altitude_target, false);
    write_enum(file, aircraft->autothrottle_active_mode, false);
    write_enum(file, aircraft->autothrottle_armed_mode, false);
    write_bool(file, aircraft->master_warning, false);
    write_bool(file, aircraft->master_caution, false);
    write_bool(file, aircraft->fire_warning, false);
    write_float(file, aircraft->drift_angle, false);
    write_float(file, aircraft->wind_direction, false);
    write_float(file, aircraft->wind_speed, false);
    write_float(file, aircraft->mass, false);
    write_float(file, aircraft->center_of_gravity, false);
    write_float(file, aircraft->percent_mac, true);
}

void write_anti_ice_systems(FILE* const restrict file, const aircraft_record* const restrict aircraft) {
    for (unsigned char i=0; i!=aircraft->aircraft->num_anti_ice_systems; i++) {
        if (aircraft->anti_ice_systems[i].active.null &&
            aircraft->anti_ice_systems[i].mode.null &&
            aircraft->anti_ice_systems[i].current.null &&
            aircraft->anti_ice_systems[i].fluid_quantity.null &&
            aircraft->anti_ice_systems[i].fluid_flow_rate.null &&
            aircraft->anti_ice_systems[i].vacuum.null)
            continue;

        write_raw_unsigned_int(file, aircraft->aircraft->id, false);
        write_timestamp(file, aircraft->timestamp, false);
        write_raw_unsigned_int(file, i, false);
        write_bool(file, aircraft->anti_ice_systems[i].active, false);
        write_enum(file, aircraft->anti_ice_systems[i].mode, false);
        write_float(file, aircraft->anti_ice_systems[i].current, false);
        write_float(file, aircraft->anti_ice_systems[i].fluid_quantity, false);
        write_float(file, aircraft->anti_ice_systems[i].fluid_flow_rate, false);
        write_float(file, aircraft->anti_ice_systems[i].vacuum, true);
    }
}

void write_bleed_air_systems(FILE* const restrict file, const aircraft_record* const restrict aircraft) {
    for (unsigned char i=0; i!=aircraft->aircraft->num_bleed_air_systems; i++) {
        if (aircraft->bleed_air_systems[i].active.null &&
            aircraft->bleed_air_systems[i].pressure.null &&
            aircraft->bleed_air_systems[i].temperature.null)
            continue;

        write_raw_unsigned_int(file, aircraft->aircraft->id, false);
        write_timestamp(file, aircraft->timestamp, false);
        write_raw_unsigned_int(file, i, false);
        write_bool(file, aircraft->bleed_air_systems[i].active, false);
        write_float(file, aircraft->bleed_air_systems[i].pressure, false);
        write_float(file, aircraft->bleed_air_systems[i].temperature, false);
        write_float(file, aircraft->bleed_air_systems[i].valve_position, true);
    }
}

void write_control_surfaces(FILE* const restrict file, const aircraft_record* const restrict aircraft) {
    for (unsigned char i=0; i!=aircraft->aircraft->num_control_surfaces; i++) {
        if (aircraft->control_surfaces[i].position.null)
            continue;

        write_raw_unsigned_int(file, aircraft->aircraft->id, false);
        write_timestamp(file, aircraft->timestamp, false);
        write_raw_unsigned_int(file, i, false);
        write_float(file, aircraft->control_surfaces[i].position, false);
        write_float(file, aircraft->control_surfaces[i].trim, false);
        write_float(file, aircraft->control_surfaces[i].position_factor, false);
        write_float(file, aircraft->control_surfaces[i].trim_factor, true);
    }
}

void write_displays(FILE* const restrict file, const aircraft_record* const restrict aircraft) {
    for (unsigned char i=0; i!=aircraft->aircraft->num_displays; i++) {
        if (aircraft->displays[i].active.null &&
            aircraft->displays[i].format.null)
            continue;

        write_raw_unsigned_int(file, aircraft->aircraft->id, false);
        write_timestamp(file, aircraft->timestamp, false);
        write_raw_unsigned_int(file, i, false);
        write_bool(file, aircraft->displays[i].active, false);
        write_enum(file, aircraft->displays[i].format, true);
    }
}

void write_electrical_systems(FILE* const restrict file, const aircraft_record* const restrict aircraft) {
    for (unsigned char i=0; i!=aircraft->aircraft->num_electrical_systems; i++) {
        if (aircraft->electrical_systems[i].active.null &&
            aircraft->electrical_systems[i].current.null &&
            aircraft->electrical_systems[i].potential.null &&
            aircraft->electrical_systems[i].frequency.null)
            continue;

        write_raw_unsigned_int(file, aircraft->aircraft->id, false);
        write_timestamp(file, aircraft->timestamp, false);
        write_raw_unsigned_int(file, i, false);
        write_bool(file, aircraft->electrical_systems[i].active, false);
        write_float(file, aircraft->electrical_systems[i].current, false);
        write_float(file, aircraft->electrical_systems[i].potential, false);
        write_float(file, aircraft->electrical_systems[i].frequency, true);
    }
}

void write_engine_cylinders(FILE* const restrict file, const aircraft_record* const restrict aircraft) {
    for (unsigned char e=0; e!=aircraft->aircraft->num_engines; e++) {
        for (unsigned char c=0; c!=aircraft->aircraft->cylinders_per_engine[e]; c++) {
            if (aircraft->engines[e].cylinders[c].cylinder_head_temperature.null &&
                aircraft->engines[e].cylinders[c].exhaust_gas_temperature.null)
                continue;

            write_raw_unsigned_int(file, aircraft->aircraft->id, false);
            write_timestamp(file, aircraft->timestamp, false);
            write_raw_unsigned_int(file, e+1, false);
            write_raw_unsigned_int(file, c+1, false);
            write_float(file, aircraft->engines[e].cylinders[c].cylinder_head_temperature, false);
            write_float(file, aircraft->engines[e].cylinders[c].exhaust_gas_temperature, true);
        }
    }
}

void write_engine_propellers(FILE* const restrict file, const aircraft_record* const restrict aircraft) {
    for (unsigned char e=0; e!=aircraft->aircraft->num_engines; e++) {
        for (unsigned char p=0; p!=aircraft->aircraft->propellers_per_engine[e]; p++) {
            if (aircraft->engines[e].propellers[p].rotational_velocity.null)
                continue;

            write_raw_unsigned_int(file, aircraft->aircraft->id, false);
            write_timestamp(file, aircraft->timestamp, false);
            write_raw_unsigned_int(file, e+1, false);
            write_raw_unsigned_int(file, p+1, false);
            write_float(file, aircraft->engines[e].propellers[p].rotational_velocity, true);
        }
    }
}

void write_engine_spools(FILE* const restrict file, const aircraft_record* const restrict aircraft) {
    for (unsigned char e=0; e!=aircraft->aircraft->num_engines; e++) {
        for (unsigned char s=0; s!=aircraft->aircraft->spools_per_engine[e]; s++) {
            if (aircraft->engines[e].spools[s].n.null &&
                aircraft->engines[e].spools[s].rotational_velocity.null)
                continue;

            write_raw_unsigned_int(file, aircraft->aircraft->id, false);
            write_timestamp(file, aircraft->timestamp, false);
            write_raw_unsigned_int(file, e+1, false);
            write_raw_unsigned_int(file, s+1, false);
            write_float(file, aircraft->engines[e].spools[s].n, false);
            write_float(file, aircraft->engines[e].spools[s].rotational_velocity, true);
        }
    }
}

void write_engines(FILE* const restrict file, const aircraft_record* const restrict aircraft) {
    for (unsigned char i=0; i!=aircraft->aircraft->num_engines; i++) {
        if (aircraft->engines[i].fuel_flow.null &&
            aircraft->engines[i].fuel_pressure.null &&
            aircraft->engines[i].vibration.null &&
            aircraft->engines[i].thrust_lever_position.null &&
            aircraft->engines[i].reverser_position.null &&
            aircraft->engines[i].reverser_lever_stowed.null &&
            aircraft->engines[i].throttle_position.null &&
            aircraft->engines[i].mixture_lever_position.null &&
            aircraft->engines[i].propeller_lever_position.null &&
            aircraft->engines[i].magneto_position.null &&
            aircraft->engines[i].carburetor_heat_lever_position.null &&
            aircraft->engines[i].cowl_flap_lever_position.null &&
            aircraft->engines[i].altitude_throttle_position.null &&
            aircraft->engines[i].condition_lever_position.null &&
            aircraft->engines[i].beta_position.null &&
            aircraft->engines[i].ignition_mode.null &&
            aircraft->engines[i].autothrottle_active.null &&
            aircraft->engines[i].fuel_source.null &&
            aircraft->engines[i].reverser_opened.null &&
            aircraft->engines[i].torque.null &&
            aircraft->engines[i].torque_factor.null &&
            aircraft->engines[i].autofeather_armed.null &&
            aircraft->engines[i].manifold_pressure.null &&
            aircraft->engines[i].thrust.null &&
            aircraft->engines[i].percent_thrust.null &&
            aircraft->engines[i].power.null &&
            aircraft->engines[i].percent_power.null &&
            aircraft->engines[i].engine_pressure_ratio.null &&
            aircraft->engines[i].exhaust_gas_temperature.null &&
            aircraft->engines[i].interstage_turbine_temperature.null &&
            aircraft->engines[i].turbine_inlet_temperature.null &&
            aircraft->engines[i].oil_pressure.null &&
            aircraft->engines[i].oil_temperature.null)
            continue;

        write_raw_unsigned_int(file, aircraft->aircraft->id, false);
        write_timestamp(file, aircraft->timestamp, false);
        write_raw_unsigned_int(file, i+1, false);
        write_float(file, aircraft->engines[i].fuel_flow, false);
        write_float(file, aircraft->engines[i].fuel_pressure, false);
        write_float(file, aircraft->engines[i].vibration, false);
        write_float(file, aircraft->engines[i].thrust_lever_position, false);
        write_float(file, aircraft->engines[i].reverser_position, false);
        write_bool(file, aircraft->engines[i].reverser_lever_stowed, false);
        write_float(file, aircraft->engines[i].throttle_position, false);
        write_float(file, aircraft->engines[i].mixture_lever_position, false);
        write_float(file, aircraft->engines[i].propeller_lever_position, false);
        write_enum(file, aircraft->engines[i].magneto_position, false);
        write_float(file, aircraft->engines[i].carburetor_heat_lever_position, false);
        write_float(file, aircraft->engines[i].cowl_flap_lever_position, false);
        write_float(file, aircraft->engines[i].altitude_throttle_position, false);
        write_float(file, aircraft->engines[i].condition_lever_position, false);
        write_float(file, aircraft->engines[i].beta_position, false);
        write_enum(file, aircraft->engines[i].ignition_mode, false);
        write_bool(file, aircraft->engines[i].autothrottle_active, false);
        write_enum(file, aircraft->engines[i].fuel_source, false);
        write_bool(file, aircraft->engines[i].reverser_opened, false);
        write_float(file, aircraft->engines[i].torque, false);
        write_float(file, aircraft->engines[i].torque_factor, false);
        write_bool(file, aircraft->engines[i].autofeather_armed, false);
        write_float(file, aircraft->engines[i].manifold_pressure, false);
        write_float(file, aircraft->engines[i].thrust, false);
        write_float(file, aircraft->engines[i].percent_thrust, false);
        write_float(file, aircraft->engines[i].power, false);
        write_float(file, aircraft->engines[i].percent_power, false);
        write_float(file, aircraft->engines[i].engine_pressure_ratio, false);
        write_float(file, aircraft->engines[i].exhaust_gas_temperature, false);
        write_float(file, aircraft->engines[i].interstage_turbine_temperature, false);
        write_float(file, aircraft->engines[i].turbine_inlet_temperature, false);
        write_float(file, aircraft->engines[i].oil_pressure, false);
        write_float(file, aircraft->engines[i].oil_temperature, true);
    }
}

void write_flight_controls(FILE* const restrict file, const aircraft_record* const restrict aircraft) {
    for (unsigned char s=0; s!=aircraft->aircraft->num_flight_control_sets; s++) {
        for (unsigned char c=0; c!=aircraft->aircraft->num_flight_controls; c++) {
            if (aircraft->flight_controls[s][c].position.null &&
                aircraft->flight_controls[s][c].shaker.null &&
                aircraft->flight_controls[s][c].pusher.null)
                continue;

            write_raw_unsigned_int(file, aircraft->aircraft->id, false);
            write_timestamp(file, aircraft->timestamp, false);
            write_raw_unsigned_int(file, s, false);
            write_raw_unsigned_int(file, c, false);
            write_float(file, aircraft->flight_controls[s][c].position, false);
            write_bool(file, aircraft->flight_controls[s][c].shaker, false);
            write_bool(file, aircraft->flight_controls[s][c].pusher, true);
        }
    }
}

void write_fuel_tanks(FILE* const restrict file, const aircraft_record* const restrict aircraft) {
    for (unsigned char i=0; i!=aircraft->aircraft->num_fuel_tanks; i++) {
        if (aircraft->fuel_tanks[i].quantity.null &&
            aircraft->fuel_tanks[i].quantity_weight.null &&
            aircraft->fuel_tanks[i].temperature.null)
            continue;

        write_raw_unsigned_int(file, aircraft->aircraft->id, false);
        write_timestamp(file, aircraft->timestamp, false);
        write_raw_unsigned_int(file, i, false);
        write_float(file, aircraft->fuel_tanks[i].quantity, false);
        write_float(file, aircraft->fuel_tanks[i].quantity_weight, false);
        write_float(file, aircraft->fuel_tanks[i].temperature, true);
    }
}

void write_ice_detection_systems(FILE* const restrict file, const aircraft_record* const restrict aircraft) {
    for (unsigned char i=0; i!=aircraft->aircraft->num_ice_detection_systems; i++) {
        if (aircraft->ice_detection_systems[i].ice_detected.null)
            continue;

        write_raw_unsigned_int(file, aircraft->aircraft->id, false);
        write_timestamp(file, aircraft->timestamp, false);
        write_raw_unsigned_int(file, i, false);
        write_bool(file, aircraft->ice_detection_systems[i].ice_detected, true);
    }
}

void write_hydraulic_systems(FILE* const restrict file, const aircraft_record* const restrict aircraft) {
    for (unsigned char i=0; i!=aircraft->aircraft->num_hydraulic_systems; i++) {
        if (aircraft->hydraulic_systems[i].pressure.null &&
            aircraft->hydraulic_systems[i].temperature.null &&
            aircraft->hydraulic_systems[i].fluid_quantity.null &&
            aircraft->hydraulic_systems[i].fluid_quantity_percent.null)
            continue;

        write_raw_unsigned_int(file, aircraft->aircraft->id, false);
        write_timestamp(file, aircraft->timestamp, false);
        write_raw_unsigned_int(file, i, false);
        write_float(file, aircraft->hydraulic_systems[i].pressure, false);
        write_float(file, aircraft->hydraulic_systems[i].temperature, false);
        write_float(file, aircraft->hydraulic_systems[i].fluid_quantity, false);
        write_float(file, aircraft->hydraulic_systems[i].fluid_quantity_percent, true);
    }
}

void write_instrument_sets(FILE* const restrict file, const aircraft_record* const restrict aircraft) {
    for (unsigned char i=0; i!=aircraft->aircraft->num_instrument_sets; i++) {
        if (aircraft->instrument_sets[i].flight_director.null &&
            aircraft->instrument_sets[i].ins.null &&
            aircraft->instrument_sets[i].gps.null &&
            aircraft->instrument_sets[i].adahrs.null &&
            aircraft->instrument_sets[i].fms.null &&
            aircraft->instrument_sets[i].nav_radio.null &&
            aircraft->instrument_sets[i].adf.null &&
            aircraft->instrument_sets[i].pitot_static_system.null &&
            aircraft->instrument_sets[i].cdi_source.null &&
            aircraft->instrument_sets[i].obs.null &&
            aircraft->instrument_sets[i].course.null &&
            aircraft->instrument_sets[i].altitude_bug.null &&
            aircraft->instrument_sets[i].decision_height.null &&
            aircraft->instrument_sets[i].indicated_airspeed_bug.null &&
            aircraft->instrument_sets[i].mach_bug.null &&
            aircraft->instrument_sets[i].vertical_speed_bug.null &&
            aircraft->instrument_sets[i].flight_path_angle_bug.null &&
            aircraft->instrument_sets[i].heading_bug.null &&
            aircraft->instrument_sets[i].track_bug.null &&
            aircraft->instrument_sets[i].indicated_altitude.null &&
            aircraft->instrument_sets[i].altimeter_setting.null &&
            aircraft->instrument_sets[i].flight_director_active.null &&
            aircraft->instrument_sets[i].flight_director_pitch.null &&
            aircraft->instrument_sets[i].flight_director_roll.null)
            continue;

        write_raw_unsigned_int(file, aircraft->aircraft->id, false);
        write_timestamp(file, aircraft->timestamp, false);
        write_raw_unsigned_int(file, i, false);
        write_enum(file, aircraft->instrument_sets[i].flight_director, false);
        write_enum(file, aircraft->instrument_sets[i].ins, false);
        write_enum(file, aircraft->instrument_sets[i].gps, false);
        write_enum(file, aircraft->instrument_sets[i].adahrs, false);
        write_enum(file, aircraft->instrument_sets[i].fms, false);
        write_enum(file, aircraft->instrument_sets[i].nav_radio, false);
        write_enum(file, aircraft->instrument_sets[i].adf, false);
        write_enum(file, aircraft->instrument_sets[i].pitot_static_system, false);
        write_enum(file, aircraft->instrument_sets[i].cdi_source, false);
        write_float(file, aircraft->instrument_sets[i].obs, false);
        write_float(file, aircraft->instrument_sets[i].course, false);
        write_float(file, aircraft->instrument_sets[i].altitude_bug, false);
        write_float(file, aircraft->instrument_sets[i].decision_height, false);
        write_float(file, aircraft->instrument_sets[i].indicated_airspeed_bug, false);
        write_float(file, aircraft->instrument_sets[i].mach_bug, false);
        write_float(file, aircraft->instrument_sets[i].vertical_speed_bug, false);
        write_float(file, aircraft->instrument_sets[i].flight_path_angle_bug, false);
        write_float(file, aircraft->instrument_sets[i].heading_bug, false);
        write_float(file, aircraft->instrument_sets[i].track_bug, false);
        write_float(file, aircraft->instrument_sets[i].indicated_altitude, false);
        write_float(file, aircraft->instrument_sets[i].altimeter_setting, false);
        write_bool(file, aircraft->instrument_sets[i].flight_director_active, false);
        write_float(file, aircraft->instrument_sets[i].flight_director_pitch, false);
        write_float(file, aircraft->instrument_sets[i].flight_director_roll, true);

    }
}

void write_landing_gear_tires(FILE* const restrict file, const aircraft_record* const restrict aircraft) {
    for (unsigned char truck=0; truck!=aircraft->aircraft->num_trucks; truck++) {
        for (unsigned char tire=0; tire!=aircraft->aircraft->tires_per_truck[truck]; tire++) {
            if (aircraft->trucks[truck].tires[tire].brake_temperature.null &&
                aircraft->trucks[truck].tires[tire].air_pressure.null)
                continue;

            write_raw_unsigned_int(file, aircraft->aircraft->id, false);
            write_timestamp(file, aircraft->timestamp, false);
            write_raw_unsigned_int(file, truck, false);
            write_raw_unsigned_int(file, tire, false);
            write_float(file, aircraft->trucks[truck].tires[tire].brake_temperature, false);
            write_float(file, aircraft->trucks[truck].tires[tire].air_pressure, true);
        }
    }
}

void write_landing_gear_trucks(FILE* const restrict file, const aircraft_record* const restrict aircraft) {
    for (unsigned char i=0; i!=aircraft->aircraft->num_trucks; i++) {
        if (aircraft->trucks[i].door_state.null &&
            aircraft->trucks[i].weight_on_wheels.null) continue;
        
        write_raw_unsigned_int(file, aircraft->aircraft->id, false);
        write_timestamp(file, aircraft->timestamp, false);
        write_raw_unsigned_int(file, i, false);
        write_enum(file, aircraft->trucks[i].door_state, false);
        write_bool(file, aircraft->trucks[i].weight_on_wheels, true);
    }
}

void write_navigation_systems(FILE* const restrict file, const aircraft_record* const restrict aircraft) {
    for (unsigned char i=0; i!=aircraft->aircraft->num_navigation_systems; i++) {
        if (aircraft->navigation_systems[i].active.null &&
            aircraft->navigation_systems[i].mode.null &&
            aircraft->navigation_systems[i].desired_track.null &&
            aircraft->navigation_systems[i].course.null &&
            aircraft->navigation_systems[i].bearing.null &&
            aircraft->navigation_systems[i].course_deviation.null &&
            aircraft->navigation_systems[i].lateral_deviation.null &&
            aircraft->navigation_systems[i].vertical_deviation.null &&
            aircraft->navigation_systems[i].lateral_deviation_factor.null &&
            aircraft->navigation_systems[i].vertical_deviation_factor.null &&
            aircraft->navigation_systems[i].active_waypoint.null &&
            aircraft->navigation_systems[i].distance_to_waypoint.null &&
            aircraft->navigation_systems[i].radio.null)
            continue;

        write_raw_unsigned_int(file, aircraft->aircraft->id, false);
        write_timestamp(file, aircraft->timestamp, false);
        write_raw_unsigned_int(file, i, false);
        write_bool(file, aircraft->navigation_systems[i].active, false);
        write_enum(file, aircraft->navigation_systems[i].mode, false);
        write_float(file, aircraft->navigation_systems[i].desired_track, false);
        write_float(file, aircraft->navigation_systems[i].course, false);
        write_float(file, aircraft->navigation_systems[i].bearing, false);
        write_float(file, aircraft->navigation_systems[i].course_deviation, false);
        write_float(file, aircraft->navigation_systems[i].lateral_deviation, false);
        write_float(file, aircraft->navigation_systems[i].vertical_deviation, false);
        write_float(file, aircraft->navigation_systems[i].lateral_deviation_factor, false);
        write_float(file, aircraft->navigation_systems[i].vertical_deviation_factor, false);
        write_string(file, aircraft->navigation_systems[i].active_waypoint, false);
        write_float(file, aircraft->navigation_systems[i].distance_to_waypoint, false);
        write_enum(file, aircraft->navigation_systems[i].radio, true);
    }
}

void write_marker_beacons(FILE* const restrict file, const aircraft_record* const restrict aircraft) {
    for (unsigned char i=0; i!=aircraft->aircraft->num_marker_beacons; i++) {
        if (aircraft->marker_beacons[i].outer.null &&
            aircraft->marker_beacons[i].middle.null &&
            aircraft->marker_beacons[i].inner.null)
            continue;

        write_raw_unsigned_int(file, aircraft->aircraft->id, false);
        write_timestamp(file, aircraft->timestamp, false);
        write_raw_unsigned_int(file, i, false);
        write_bool(file, aircraft->marker_beacons[i].outer, false);
        write_bool(file, aircraft->marker_beacons[i].middle, false);
        write_bool(file, aircraft->marker_beacons[i].inner, true);
    }
}

void write_packs(FILE* const restrict file, const aircraft_record* const restrict aircraft) {
    for (unsigned char i=0; i!=aircraft->aircraft->num_packs; i++) {
        if (aircraft->packs[i].active.null &&
            aircraft->packs[i].air_pressure.null &&
            aircraft->packs[i].air_temperature.null)
            continue;

        write_raw_unsigned_int(file, aircraft->aircraft->id, false);
        write_timestamp(file, aircraft->timestamp, false);
        write_raw_unsigned_int(file, i+1, false);
        write_bool(file, aircraft->packs[i].active, false);
        write_float(file, aircraft->packs[i].air_pressure, false);
        write_float(file, aircraft->packs[i].air_temperature, true);
    }
}

void write_pitot_static_systems(FILE* const restrict file, const aircraft_record* const restrict aircraft) {
    for (unsigned char i=0; i!=aircraft->aircraft->num_pitot_static_systems; i++) {
        if (aircraft->pitot_static_systems[i].static_air_temperature.null &&
            aircraft->pitot_static_systems[i].total_air_temperature.null &&
            aircraft->pitot_static_systems[i].temperature_deviation.null &&
            aircraft->pitot_static_systems[i].air_pressure.null &&
            aircraft->pitot_static_systems[i].air_density.null &&
            aircraft->pitot_static_systems[i].pressure_altitude.null &&
            aircraft->pitot_static_systems[i].density_altitude.null &&
            aircraft->pitot_static_systems[i].indicated_airspeed.null &&
            aircraft->pitot_static_systems[i].calibrated_airspeed.null &&
            aircraft->pitot_static_systems[i].true_airpseed.null &&
            aircraft->pitot_static_systems[i].speed_of_sound.null &&
            aircraft->pitot_static_systems[i].mach.null &&
            aircraft->pitot_static_systems[i].vertical_speed.null &&
            aircraft->pitot_static_systems[i].angle_of_attack.null &&
            aircraft->pitot_static_systems[i].angle_of_sideslip.null)
            continue;

        write_raw_unsigned_int(file, aircraft->aircraft->id, false);
        write_timestamp(file, aircraft->timestamp, false);
        write_raw_unsigned_int(file, i, false);
        write_float(file, aircraft->pitot_static_systems[i].static_air_temperature, false);
        write_float(file, aircraft->pitot_static_systems[i].total_air_temperature, false);
        write_float(file, aircraft->pitot_static_systems[i].temperature_deviation, false);
        write_float(file, aircraft->pitot_static_systems[i].air_pressure, false);
        write_float(file, aircraft->pitot_static_systems[i].air_density, false);
        write_float(file, aircraft->pitot_static_systems[i].pressure_altitude, false);
        write_float(file, aircraft->pitot_static_systems[i].density_altitude, false);
        write_float(file, aircraft->pitot_static_systems[i].indicated_airspeed, false);
        write_float(file, aircraft->pitot_static_systems[i].calibrated_airspeed, false);
        write_float(file, aircraft->pitot_static_systems[i].true_airpseed, false);
        write_float(file, aircraft->pitot_static_systems[i].speed_of_sound, false);
        write_float(file, aircraft->pitot_static_systems[i].mach, false);
        write_float(file, aircraft->pitot_static_systems[i].vertical_speed, false);
        write_float(file, aircraft->pitot_static_systems[i].angle_of_attack, false);
        write_float(file, aircraft->pitot_static_systems[i].angle_of_sideslip, true);
    }
}

void write_pneumatic_systems(FILE* const restrict file, const aircraft_record* const restrict aircraft) {
    for (unsigned char i=0; i!=aircraft->aircraft->num_pneumatic_systems; i++) {
        if (aircraft->pneumatic_systems[i].pressure.null)
            continue;

        write_raw_unsigned_int(file, aircraft->aircraft->id, false);
        write_timestamp(file, aircraft->timestamp, false);
        write_raw_unsigned_int(file, i, false);
        write_float(file, aircraft->pneumatic_systems[i].pressure, true);
    }
}

void write_pressurization_system_valves(FILE* const restrict file, const aircraft_record* const restrict aircraft) {
    for (unsigned char e=0; e!=aircraft->aircraft->num_pressurization_systems; e++) {
        for (unsigned char v=0; v!=aircraft->aircraft->valves_per_pressurization_system[e]; v++) {
            if (aircraft->pressurization_systems[e].valves[v].position.null)
                continue;

            write_raw_unsigned_int(file, aircraft->aircraft->id, false);
            write_timestamp(file, aircraft->timestamp, false);
            write_raw_unsigned_int(file, e+1, false);
            write_raw_unsigned_int(file, v+1, false);
            write_float(file, aircraft->pressurization_systems[e].valves[v].position, true);
        }
    }
}


void write_pressurization_systems(FILE* const restrict file, const aircraft_record* const restrict aircraft) {
    for (unsigned char i=0; i!=aircraft->aircraft->num_pressurization_systems; i++) {
        if (aircraft->pressurization_systems[i].mode.null &&
            aircraft->pressurization_systems[i].differential_pressure.null &&
            aircraft->pressurization_systems[i].cabin_altitude.null &&
            aircraft->pressurization_systems[i].cabin_rate.null &&
            aircraft->pressurization_systems[i].target_altitude.null)
            continue;

        write_raw_unsigned_int(file, aircraft->aircraft->id, false);
        write_timestamp(file, aircraft->timestamp, false);
        write_raw_unsigned_int(file, i, false);
        write_enum(file, aircraft->pressurization_systems[i].mode, false);
        write_float(file, aircraft->pressurization_systems[i].differential_pressure, false);
        write_float(file, aircraft->pressurization_systems[i].cabin_altitude, false);
        write_float(file, aircraft->pressurization_systems[i].cabin_rate, false);
        write_float(file, aircraft->pressurization_systems[i].target_altitude, true);
    }
}

void write_position_sensors(FILE* const restrict file, const aircraft_record* const restrict aircraft) {
    for (unsigned char i=0; i!=aircraft->aircraft->num_position_sensors; i++) {
            if (aircraft->position_sensors[i].state.null &&
                aircraft->position_sensors[i].roll.null &&
                aircraft->position_sensors[i].pitch.null &&
                aircraft->position_sensors[i].true_heading.null &&
                aircraft->position_sensors[i].magnetic_heading.null &&
                aircraft->position_sensors[i].grid_heading.null &&
                aircraft->position_sensors[i].true_track.null &&
                aircraft->position_sensors[i].magnetic_track.null &&
                aircraft->position_sensors[i].grid_track.null &&
                aircraft->position_sensors[i].longitude.null &&
                aircraft->position_sensors[i].latitude.null &&
                aircraft->position_sensors[i].altitude.null &&
                aircraft->position_sensors[i].ground_elevation.null &&
                aircraft->position_sensors[i].height_agl.null &&
                aircraft->position_sensors[i].pitch_rate.null &&
                aircraft->position_sensors[i].roll_rate.null &&
                aircraft->position_sensors[i].yaw_rate.null &&
                aircraft->position_sensors[i].heading_rate.null &&
                aircraft->position_sensors[i].ground_speed.null &&
                aircraft->position_sensors[i].vertical_speed.null &&
                aircraft->position_sensors[i].climb_gradient.null &&
                aircraft->position_sensors[i].climb_angle.null &&
                aircraft->position_sensors[i].horizontal_figure_of_merit.null &&
                aircraft->position_sensors[i].horizontal_protection_level.null &&
                aircraft->position_sensors[i].vertical_figure_of_merit.null &&
                aircraft->position_sensors[i].vertical_protection_level.null)
            continue;

        write_raw_unsigned_int(file, aircraft->aircraft->id, false);
        write_timestamp(file, aircraft->timestamp, false);
        write_raw_unsigned_int(file, i, false);
        write_enum(file, aircraft->position_sensors[i].state, false);
        write_float(file, aircraft->position_sensors[i].roll, false);
        write_float(file, aircraft->position_sensors[i].pitch, false);
        write_float(file, aircraft->position_sensors[i].true_heading, false);
        write_float(file, aircraft->position_sensors[i].magnetic_heading, false);
        write_float(file, aircraft->position_sensors[i].grid_heading, false);
        write_float(file, aircraft->position_sensors[i].true_track, false);
        write_float(file, aircraft->position_sensors[i].magnetic_track, false);
        write_float(file, aircraft->position_sensors[i].grid_track, false);
        write_float(file, aircraft->position_sensors[i].latitude, false);
        write_float(file, aircraft->position_sensors[i].longitude, false);
        write_float(file, aircraft->position_sensors[i].altitude, false);
        write_float(file, aircraft->position_sensors[i].ground_elevation, false);
        write_float(file, aircraft->position_sensors[i].height_agl, false);
        write_float(file, aircraft->position_sensors[i].pitch_rate, false);
        write_float(file, aircraft->position_sensors[i].roll_rate, false);
        write_float(file, aircraft->position_sensors[i].yaw_rate, false);
        write_float(file, aircraft->position_sensors[i].heading_rate, false);
        write_float(file, aircraft->position_sensors[i].ground_speed, false);
        write_float(file, aircraft->position_sensors[i].vertical_speed, false);
        write_float(file, aircraft->position_sensors[i].climb_gradient, false);
        write_float(file, aircraft->position_sensors[i].climb_angle, false);
        write_float(file, aircraft->position_sensors[i].horizontal_figure_of_merit, false);
        write_float(file, aircraft->position_sensors[i].horizontal_protection_level, false);
        write_float(file, aircraft->position_sensors[i].vertical_figure_of_merit, false);
        write_float(file, aircraft->position_sensors[i].vertical_protection_level, true);
    }
}

void write_radios(FILE* const restrict file, const aircraft_record* const restrict aircraft) {
    for (unsigned char i=0; i!=aircraft->aircraft->num_radios; i++) {
        if (aircraft->radios[i].active.null &&
            aircraft->radios[i].monitoring.null &&
            aircraft->radios[i].monitoring_standby.null &&
            aircraft->radios[i].transmitting.null &&
            aircraft->radios[i].receiving.null &&
            aircraft->radios[i].squelched.null &&
            aircraft->radios[i].beat_frequency_oscillation.null &&
            aircraft->radios[i].ident.null &&
            aircraft->radios[i].single_sideband.null &&
            aircraft->radios[i].active_frequency.null &&
            aircraft->radios[i].standby_frequency.null &&
            aircraft->radios[i].volume.null &&
            aircraft->radios[i].squelch.null)
            continue;

        write_raw_unsigned_int(file, aircraft->aircraft->id, false);
        write_timestamp(file, aircraft->timestamp, false);
        write_raw_unsigned_int(file, i, false);
        write_bool(file, aircraft->radios[i].active, false);
        write_bool(file, aircraft->radios[i].monitoring, false);
        write_bool(file, aircraft->radios[i].monitoring_standby, false);
        write_bool(file, aircraft->radios[i].transmitting, false);
        write_bool(file, aircraft->radios[i].receiving, false);
        write_bool(file, aircraft->radios[i].squelched, false);
        write_bool(file, aircraft->radios[i].beat_frequency_oscillation, false);
        write_bool(file, aircraft->radios[i].ident, false);
        write_bool(file, aircraft->radios[i].single_sideband, false);
        write_int(file, aircraft->radios[i].active_frequency, false);
        write_int(file, aircraft->radios[i].standby_frequency, false);
        write_float(file, aircraft->radios[i].volume, false);
        write_float(file, aircraft->radios[i].squelch, true);
    }
}

void write_radio_altimeters(FILE* const restrict file, const aircraft_record* const restrict aircraft) {
    for (unsigned char i=0; i!=aircraft->aircraft->num_radio_altimeters; i++) {
        if (aircraft->radio_altimeters[i].state.null &&
            aircraft->radio_altimeters[i].altitude.null &&
            aircraft->radio_altimeters[i].alert_altitude.null)
            continue;

        write_raw_unsigned_int(file, aircraft->aircraft->id, false);
        write_timestamp(file, aircraft->timestamp, false);
        write_raw_unsigned_int(file, i, false);
        write_enum(file, aircraft->radio_altimeters[i].state, false);
        write_float(file, aircraft->radio_altimeters[i].altitude, false);
        write_float(file, aircraft->radio_altimeters[i].alert_altitude, true);
    }
}

void write_rotors(FILE* const restrict file, const aircraft_record* const restrict aircraft) {
    for (unsigned char i=0; i!=aircraft->aircraft->num_rotors; i++) {
        if (aircraft->rotors[i].rotational_velocity.null &&
            aircraft->rotors[i].blade_angle.null)
            continue;

        write_raw_unsigned_int(file, aircraft->aircraft->id, false);
        write_timestamp(file, aircraft->timestamp, false);
        write_raw_unsigned_int(file, i+1, false);
        write_float(file, aircraft->rotors[i].rotational_velocity, false);
        write_float(file, aircraft->rotors[i].blade_angle, true);
    }
}

void write_traffic_systems(FILE* const restrict file, const aircraft_record* const restrict aircraft) {
    for (unsigned char i=0; i!=aircraft->aircraft->num_traffic_systems; i++) {
        if (aircraft->traffic_systems[i].mode.null &&
            aircraft->traffic_systems[i].traffic_advisory.null &&
            aircraft->traffic_systems[i].resolution_advisory.null &&
            aircraft->traffic_systems[i].horizontal_resolution_advisory.null &&
            aircraft->traffic_systems[i].vertical_resolution_advisory.null)
            continue;

        write_raw_unsigned_int(file, aircraft->aircraft->id, false);
        write_timestamp(file, aircraft->timestamp, false);
        write_raw_unsigned_int(file, i, false);
        write_enum(file, aircraft->traffic_systems[i].mode, false);
        write_bool(file, aircraft->traffic_systems[i].traffic_advisory, false);
        write_bool(file, aircraft->traffic_systems[i].resolution_advisory, false);
        write_enum(file, aircraft->traffic_systems[i].horizontal_resolution_advisory, false);
        write_enum(file, aircraft->traffic_systems[i].vertical_resolution_advisory, true);
    }
}

void write_transponders(FILE* const restrict file, const aircraft_record* const restrict aircraft) {
    for (unsigned char i=0; i!=aircraft->aircraft->num_transponders; i++) {
        if (aircraft->transponders[i].mode.null &&
            aircraft->transponders[i].mode_3a_code.null &&
            aircraft->transponders[i].mode_s_code.null &&
            aircraft->transponders[i].flight_id.null &&
            aircraft->transponders[i].replying.null)
            continue;

        write_raw_unsigned_int(file, aircraft->aircraft->id, false);
        write_timestamp(file, aircraft->timestamp, false);
        write_raw_unsigned_int(file, i+1, false);
        write_enum(file, aircraft->transponders[i].mode, false);
        write_int(file, aircraft->transponders[i].mode_3a_code, false);
        write_int(file, aircraft->transponders[i].mode_s_code, false);
        write_string(file, aircraft->transponders[i].flight_id, false);
        write_bool(file, aircraft->transponders[i].replying, true);
    }
}

void write_enum(FILE* const restrict file, optional value, bool end) {
    if (value.null) {
        write_null(file, end);
        return;
    }

    char value_str[3];
    sprintf(value_str, "%i", value.c);
    write_raw(file, value_str, end);
}

void write_int(FILE* const restrict file, optional value, bool end) {
    if (value.null) {
        write_null(file, end);
        return;
    }

    char value_str[11];
    sprintf(value_str, "%i", value.i);
    write_raw(file, value_str, end);
}

void write_raw_unsigned_int(FILE* const restrict file, unsigned int value, bool end) {
    char value_str[11];
    sprintf(value_str, "%u", value);
    write_raw(file, value_str, end);
}

void write_float(FILE* const restrict file, optional value, bool end) {
    if (value.null) {
        write_null(file, end);
        return;
    }

    char value_str[23];
    sprintf(value_str, "%g", value.f);
    write_raw(file, value_str, end);
}

void write_bool(FILE* const restrict file, optional value, bool end) {
    if (value.null) {
        write_null(file, end);
        return;
    }

    if (value.b) write_raw(file, "t", end);
    else write_raw(file, "f", end);
}

void write_timestamp(FILE* const restrict file, time_m value, bool end) {
    struct tm *time = gmtime(&(value.seconds));
    char time_str[30];
    // 2015-01-07 16:32:27.111546+00
    strftime(time_str, 30, "%F %T", time);
    sprintf(time_str, "%s.%03d+00", time_str, value.milliseconds);
    write_raw(file, time_str, end);
}

void write_string(FILE* const restrict file, optional value, bool end) {
    if (value.null) {
        write_null(file, end);
        return;
    }

    write_raw(file, value.s, end);
}

void write_position(FILE* const restrict file, optional x, optional y, optional z, bool end) {
    if (x.null || y.null || z.null) {
        write_null(file, end);
        return;
    }

    char str[72];
    sprintf(str, "SRID=4326;POINT(%g %g %g)", x.f, y.f, z.f);
    write_raw(file, str, end);
}

void write_null(FILE* const restrict file, bool end) {
    write_raw(file, "\\N", end);
}

void write_raw(FILE* const restrict file, char *value, bool end) {
    fprintf(file, "%s", value);
    if (end) fprintf(file, "\n");
    else fprintf(file, "\t");
}

void writer_free(writer* const restrict writer) {
    fclose(writer->telemetry);
    fclose(writer->anti_ice_systems);
    fclose(writer->bleed_air_systems);
    fclose(writer->control_surfaces);
    fclose(writer->displays);
    fclose(writer->electrical_systems);
    fclose(writer->engine_cylinders);
    fclose(writer->engines);
    fclose(writer->engine_propellers);
    fclose(writer->engine_spools);
    fclose(writer->flight_controls);
    fclose(writer->fuel_tanks);
    fclose(writer->hydraulic_systems);
    fclose(writer->ice_detection_systems);
    fclose(writer->instrument_sets);
    fclose(writer->landing_gear_tires);
    fclose(writer->landing_gear_trucks);
    fclose(writer->marker_beacons);
    fclose(writer->navigation_systems);
    fclose(writer->packs);
    fclose(writer->pitot_static_systems);
    fclose(writer->pneumatic_systems);
    fclose(writer->pressurization_system_valves);
    fclose(writer->pressurization_systems);
    fclose(writer->position_sensors);
    fclose(writer->radios);
    fclose(writer->radio_altimeters);
    fclose(writer->rotors);
    fclose(writer->traffic_systems);
    fclose(writer->transponders);

    free(writer);
}
