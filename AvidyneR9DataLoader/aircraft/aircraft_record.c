//
//  aircraft.c
//  AvidyneR9DataLoader
//
//  Created by Tim Morgan on 12/16/18.
//  Copyright © 2018 Tim Morgan. All rights reserved.
//

#include "aircraft_record.h"

void anti_ice_system_init(anti_ice_system* const restrict system);
void bleed_air_system_init(bleed_air_system* const restrict system);
void control_surface_init(control_surface* const restrict surface);
void display_init(display* const restrict display);
void electrical_system_init(electrical_system* const restrict system);
void engine_init(engine* const restrict engine, unsigned char num_cylinders, unsigned char num_propellers, unsigned char num_spools);
void cylinder_init(cylinder* const restrict cylinder);
void flight_control_init(flight_control* const restrict flight_control);
void fuel_tank_init(fuel_tank* const restrict fuel_tank);
void hydraulic_system_init(hydraulic_system* const restrict system);
void ice_detection_system_init(ice_detection_system* const restrict system);
void instrument_set_init(instrument_set* const restrict set);
void truck_init(truck* const restrict truck, unsigned char num_tires);
void tire_init(tire* const restrict tire);
void marker_beacon_init(marker_beacon* const restrict beacon);
void navigation_system_init(navigation_system* const restrict system);
void pack_init(pack* const restrict pack);
void pitot_static_system_init(pitot_static_system* const restrict system);
void pneumatic_system_init(pneumatic_system* const restrict system);
void pressurization_system_init(pressurization_system* const restrict system, unsigned char num_valves);
void propeller_init(propeller* const restrict propeller);
void position_sensor_init(position_sensor* const restrict sensor);
void radio_init(radio* const restrict radio);
void radio_altimeter_init(radio_altimeter* const restrict radio_altimeter);
void rotor_init(rotor* const restrict rotor);
void spool_init(spool* const restrict spool);
void traffic_system_init(traffic_system* const restrict system);
void transponder_init(transponder* const restrict transponder);
void valve_init(valve* const restrict valve);

aircraft_record *make_aircraft_record(aircraft* const aircraft) {
    aircraft_record* const restrict record = malloc(sizeof(aircraft_record));
    record->aircraft = aircraft;
    init_aircraft_record(record);
    return record;
}

void init_aircraft_record(aircraft_record* const restrict record) {
    time_m timestamp;
    timestamp.seconds = timestamp.milliseconds = 0;

    record->timestamp = timestamp;
    record->acceleration_lateral = optnull();
    record->acceleration_longitudinal = optnull();
    record->acceleration_normal = optnull();
    record->magnetic_variation = optnull();
    record->grid_convergence = optnull();
    record->fuel_totalizer_used = optnull();
    record->fuel_totalizer_remaining = optnull();
    record->fuel_totalizer_economy = optnull();
    record->fuel_totalizer_used_weight = optnull();
    record->fuel_totalizer_remaining_weight = optnull();
    record->fuel_totalizer_economy_weight = optnull();
    record->fuel_totalizer_time_remaining = optnull();
    record->autopilot_active = optnull();
    record->autopilot_mode = optnull();
    record->autopilot_lateral_active_mode = optnull();
    record->autopilot_lateral_armed_mode = optnull();
    record->autopilot_vertical_active_mode = optnull();
    record->autopilot_vertical_armed_mode = optnull();
    record->autopilot_altitude_target = optnull();
    record->autothrottle_active_mode = optnull();
    record->autothrottle_armed_mode = optnull();
    record->master_warning = optnull();
    record->master_caution = optnull();
    record->fire_warning = optnull();
    record->drift_angle = optnull();
    record->wind_direction = optnull();
    record->wind_speed = optnull();
    record->mass = optnull();
    record->center_of_gravity = optnull();
    record->percent_mac = optnull();

    record->anti_ice_systems = malloc(sizeof(anti_ice_system) * record->aircraft->num_anti_ice_systems);
    for (unsigned char i=0; i!=record->aircraft->num_anti_ice_systems; i++)
        anti_ice_system_init(&(record->anti_ice_systems[i]));

    record->bleed_air_systems = malloc(sizeof(bleed_air_system) * record->aircraft->num_bleed_air_systems);
    for (unsigned char i=0; i!=record->aircraft->num_bleed_air_systems; i++)
        bleed_air_system_init(&(record->bleed_air_systems[i]));

    record->control_surfaces = malloc(sizeof(control_surface) * record->aircraft->num_control_surfaces);
    for (unsigned char i=0; i!=record->aircraft->num_control_surfaces; i++)
        control_surface_init(&(record->control_surfaces[i]));

    record->displays = malloc(sizeof(display) * record->aircraft->num_displays);
    for (unsigned char i=0; i!=record->aircraft->num_displays; i++)
        display_init(&(record->displays[i]));

    record->electrical_systems = malloc(sizeof(electrical_system) * record->aircraft->num_electrical_systems);
    for (unsigned char i=0; i!=record->aircraft->num_electrical_systems; i++)
        electrical_system_init(&(record->electrical_systems[i]));

    record->engines = malloc(sizeof(engine) * record->aircraft->num_engines);
    for (unsigned char i=0; i!=record->aircraft->num_engines; i++)
        engine_init(&(record->engines[i]), record->aircraft->cylinders_per_engine[i], record->aircraft->propellers_per_engine[i], record->aircraft->spools_per_engine[i]);

    record->flight_controls = malloc(sizeof(flight_control*) * record->aircraft->num_flight_control_sets);
    for (unsigned char s=0; s!=record->aircraft->num_flight_control_sets; s++) {
        record->flight_controls[s] = malloc(sizeof(flight_control) * record->aircraft->num_flight_controls);
        for (unsigned char c=0; c!=record->aircraft->num_flight_controls; c++)
            flight_control_init(&(record->flight_controls[s][c]));
    }

    record->fuel_tanks = malloc(sizeof(fuel_tank) * record->aircraft->num_fuel_tanks);
    for (unsigned char i=0; i!=record->aircraft->num_fuel_tanks; i++)
        fuel_tank_init(&(record->fuel_tanks[i]));

    record->hydraulic_systems = malloc(sizeof(hydraulic_system) * record->aircraft->num_hydraulic_systems);
    for (unsigned char i=0; i!=record->aircraft->num_hydraulic_systems; i++)
        hydraulic_system_init(&(record->hydraulic_systems[i]));

    record->ice_detection_systems = malloc(sizeof(ice_detection_system) * record->aircraft->num_ice_detection_systems);
    for (unsigned char i=0; i!=record->aircraft->num_ice_detection_systems; i++)
        ice_detection_system_init(&(record->ice_detection_systems[i]));

    record->instrument_sets = malloc(sizeof(instrument_set) * record->aircraft->num_instrument_sets);
    for (unsigned char i=0; i!=record->aircraft->num_instrument_sets; i++)
        instrument_set_init(&(record->instrument_sets[i]));

    record->trucks = malloc(sizeof(truck) * record->aircraft->num_trucks);
    for (unsigned char i=0; i!=record->aircraft->num_trucks; i++)
        truck_init(&(record->trucks[i]), record->aircraft->tires_per_truck[i]);

    record->navigation_systems = malloc(sizeof(navigation_system) * record->aircraft->num_navigation_systems);
    for (unsigned char i=0; i!=record->aircraft->num_navigation_systems; i++) {
        record->navigation_systems[i].active_waypoint = optnull();
        navigation_system_init(&(record->navigation_systems[i]));
    }

    record->marker_beacons = malloc(sizeof(marker_beacon) * record->aircraft->num_marker_beacons);
    for (unsigned char i=0; i!=record->aircraft->num_marker_beacons; i++) {
        marker_beacon_init(&(record->marker_beacons[i]));
    }

    record->packs = malloc(sizeof(pack) * record->aircraft->num_packs);
    for (unsigned char i=0; i!=record->aircraft->num_packs; i++)
        pack_init(&(record->packs[i]));

    record->pitot_static_systems = malloc(sizeof(pitot_static_system) * record->aircraft->num_pitot_static_systems);
    for (unsigned char i=0; i!=record->aircraft->num_pitot_static_systems; i++)
        pitot_static_system_init(&(record->pitot_static_systems[i]));

    record->pneumatic_systems = malloc(sizeof(pneumatic_system) * record->aircraft->num_pneumatic_systems);
    for (unsigned char i=0; i!=record->aircraft->num_pneumatic_systems; i++)
        pneumatic_system_init(&(record->pneumatic_systems[i]));

    record->pressurization_systems = malloc(sizeof(pressurization_system) * record->aircraft->num_pressurization_systems);
    for (unsigned char i=0; i!=record->aircraft->num_pressurization_systems; i++)
        pressurization_system_init(&(record->pressurization_systems[i]), record->aircraft->valves_per_pressurization_system[i]);

    record->position_sensors = malloc(sizeof(position_sensor) * record->aircraft->num_position_sensors);
    for (unsigned char i=0; i!=record->aircraft->num_position_sensors; i++)
        position_sensor_init(&(record->position_sensors[i]));

    record->radios = malloc(sizeof(radio) * record->aircraft->num_radios);
    for (unsigned char i=0; i!=record->aircraft->num_radios; i++)
        radio_init(&(record->radios[i]));

    record->radio_altimeters = malloc(sizeof(radio_altimeter) * record->aircraft->num_radio_altimeters);
    for (unsigned char i=0; i!=record->aircraft->num_radio_altimeters; i++)
        radio_altimeter_init(&(record->radio_altimeters[i]));

    record->rotors = malloc(sizeof(rotor) * record->aircraft->num_rotors);
    for (unsigned char i=0; i!=record->aircraft->num_rotors; i++)
        rotor_init(&(record->rotors[i]));

    record->transponders = malloc(sizeof(transponder) * record->aircraft->num_transponders);
    for (unsigned char i=0; i!=record->aircraft->num_transponders; i++)
        transponder_init(&(record->transponders[i]));

    record->traffic_systems = malloc(sizeof(traffic_system) * record->aircraft->num_traffic_systems);
    for (unsigned char i=0; i!=record->aircraft->num_traffic_systems; i++)
        traffic_system_init(&(record->traffic_systems[i]));
}

void aircraft_record_free(aircraft_record* const restrict record) {
    for (unsigned char engine=0; engine!=record->aircraft->num_engines; engine++)
        free(record->engines[engine].cylinders);
    free(record->engines);

    for (unsigned char truck=0; truck!=record->aircraft->num_trucks; truck++)
        free(record->trucks[truck].tires);
    free(record->trucks);

    for (unsigned char system=0; system!=record->aircraft->num_pressurization_systems; system++)
        free(record->pressurization_systems[system].valves);
    free(record->pressurization_systems);

    for (unsigned char s=0; s!=record->aircraft->num_flight_control_sets; s++)
        free(record->flight_controls[s]);

    free(record->anti_ice_systems);
    free(record->bleed_air_systems);
    free(record->control_surfaces);
    free(record->displays);
    free(record->electrical_systems);
    free(record->flight_controls);
    free(record->fuel_tanks);
    free(record->hydraulic_systems);
    free(record->ice_detection_systems);
    free(record->instrument_sets);
    free(record->marker_beacons);
    free(record->navigation_systems);
    free(record->packs);
    free(record->pitot_static_systems);
    free(record->pneumatic_systems);
    free(record->position_sensors);
    free(record->radios);
    free(record->radio_altimeters);
    free(record->rotors);
    free(record->transponders);
    free(record->traffic_systems);

    free(record);
}

void anti_ice_system_init(anti_ice_system* const restrict system) {
    system->active = optnull();
    system->mode = optnull();
    system->current = optnull();
    system->fluid_quantity = optnull();
    system->fluid_flow_rate = optnull();
    system->vacuum = optnull();
}

void bleed_air_system_init(bleed_air_system* const restrict system) {
    system->active = optnull();
    system->temperature = optnull();
    system->pressure = optnull();
    system->valve_position = optnull();
}

void control_surface_init(control_surface* const restrict surface) {
    surface->position = optnull();
    surface->trim = optnull();
    surface->position_factor = optnull();
    surface->trim_factor = optnull();
}

void display_init(display* const restrict display) {
    display->active = optnull();
    display->format = optnull();
}

void electrical_system_init(electrical_system* const restrict system) {
    system->active = optnull();
    system->current = optnull();
    system->potential = optnull();
    system->frequency = optnull();
}

void engine_init(engine* const restrict engine, unsigned char num_cylinders, unsigned char num_propellers, unsigned char num_spools) {
    engine->fuel_flow = optnull();
    engine->fuel_pressure = optnull();
    engine->vibration = optnull();
    engine->thrust_lever_position = optnull();
    engine->reverser_position = optnull();
    engine->reverser_lever_stowed = optnull();
    engine->throttle_position = optnull();
    engine->mixture_lever_position = optnull();
    engine->propeller_lever_position = optnull();
    engine->magneto_position = optnull();
    engine->carburetor_heat_lever_position = optnull();
    engine->cowl_flap_lever_position = optnull();
    engine->altitude_throttle_position = optnull();
    engine->condition_lever_position = optnull();
    engine->beta_position = optnull();
    engine->ignition_mode = optnull();
    engine->autothrottle_active = optnull();
    engine->fuel_source = optnull();
    engine->reverser_opened = optnull();
    engine->thrust = optnull();
    engine->torque = optnull();
    engine->torque_factor = optnull();
    engine->autofeather_armed = optnull();
    engine->manifold_pressure = optnull();
    engine->percent_thrust = optnull();
    engine->thrust = optnull();
    engine->percent_power = optnull();
    engine->power = optnull();
    engine->percent_power = optnull();
    engine->engine_pressure_ratio = optnull();
    engine->exhaust_gas_temperature = optnull();
    engine->interstage_turbine_temperature = optnull();
    engine->turbine_inlet_temperature = optnull();
    engine->oil_pressure = optnull();
    engine->oil_temperature = optnull();

    engine->cylinders = malloc(sizeof(cylinder) * num_cylinders);
    for (unsigned char i=0; i!=num_cylinders; i++)
        cylinder_init(&(engine->cylinders[i]));

    engine->propellers = malloc(sizeof(cylinder) * num_propellers);
    for (unsigned char i=0; i!=num_propellers; i++)
        propeller_init(&(engine->propellers[i]));

    engine->spools = malloc(sizeof(cylinder) * num_spools);
    for (unsigned char i=0; i!=num_spools; i++)
        spool_init(&(engine->spools[i]));
}

void cylinder_init(cylinder* const restrict cylinder) {
    cylinder->cylinder_head_temperature = optnull();
    cylinder->exhaust_gas_temperature = optnull();
}

void flight_control_init(flight_control* const restrict flight_control) {
    flight_control->position = optnull();
    flight_control->shaker = optnull();
    flight_control->pusher = optnull();
}

void fuel_tank_init(fuel_tank* const restrict fuel_tank) {
    fuel_tank->quantity = optnull();
    fuel_tank->quantity_weight = optnull();
    fuel_tank->temperature = optnull();
}

void hydraulic_system_init(hydraulic_system* const restrict system) {
    system->pressure = optnull();
    system->temperature = optnull();
    system->fluid_quantity = optnull();
    system->fluid_quantity_percent = optnull();
}

void ice_detection_system_init(ice_detection_system* const restrict system) {
    system->ice_detected = optnull();
}

void instrument_set_init(instrument_set* const restrict set) {
    set->flight_director = optnull();
    set->ins = optnull();
    set->gps = optnull();
    set->adahrs = optnull();
    set->fms = optnull();
    set->nav_radio = optnull();
    set->adf = optnull();
    set->pitot_static_system = optnull();
    set->cdi_source = optnull();
    set->obs = optnull();
    set->course = optnull();
    set->altitude_bug = optnull();
    set->decision_height = optnull();
    set->indicated_airspeed_bug = optnull();
    set->mach_bug = optnull();
    set->vertical_speed_bug = optnull();
    set->flight_path_angle_bug = optnull();
    set->heading_bug = optnull();
    set->track_bug = optnull();
    set->indicated_altitude = optnull();
    set->altimeter_setting = optnull();
    set->flight_director_active = optnull();
    set->flight_director_pitch = optnull();
    set->flight_director_roll = optnull();
}

void truck_init(truck* const restrict truck, unsigned char num_tires) {
    truck->door_state = optnull();
    truck->weight_on_wheels = optnull();

    truck->tires = malloc(sizeof(tire) * num_tires);
    for (unsigned char i=0; i!=num_tires; i++)
        tire_init(&(truck->tires[i]));
}

void tire_init(tire* const restrict tire) {
    tire->brake_temperature = optnull();
    tire->air_pressure = optnull();
}

void marker_beacon_init(marker_beacon* const restrict beacon) {
    beacon->outer = optnull();
    beacon->middle = optnull();
    beacon->inner = optnull();
}

void navigation_system_init(navigation_system* const restrict system) {
    system->active = optnull();
    system->mode = optnull();
    system->desired_track = optnull();
    system->course = optnull();
    system->bearing = optnull();
    system->course_deviation = optnull();
    system->lateral_deviation = optnull();
    system->vertical_deviation = optnull();
    system->lateral_deviation_factor = optnull();
    system->vertical_deviation_factor = optnull();
    if (!system->active_waypoint.null) free(system->active_waypoint.s);
    system->active_waypoint = optnull();
    system->distance_to_waypoint = optnull();
    system->radio = optnull();
}

void pack_init(pack* const restrict pack) {
    pack->active = optnull();
    pack->air_pressure = optnull();
    pack->air_temperature = optnull();
}

void pitot_static_system_init(pitot_static_system* const restrict system) {
    system->static_air_temperature = optnull();
    system->total_air_temperature = optnull();
    system->temperature_deviation = optnull();
    system->air_pressure = optnull();
    system->air_density = optnull();
    system->pressure_altitude = optnull();
    system->density_altitude = optnull();
    system->indicated_airspeed = optnull();
    system->calibrated_airspeed = optnull();
    system->true_airpseed = optnull();
    system->speed_of_sound = optnull();
    system->mach = optnull();
    system->vertical_speed = optnull();
    system->angle_of_attack = optnull();
    system->angle_of_sideslip = optnull();
}

void propeller_init(propeller* const restrict propeller) {
    propeller->rotational_velocity = optnull();
}

void pneumatic_system_init(pneumatic_system* const restrict system) {
    system->pressure = optnull();
}

void pressurization_system_init(pressurization_system* const restrict system, unsigned char num_valves) {
    system->mode = optnull();
    system->differential_pressure = optnull();
    system->cabin_altitude = optnull();
    system->cabin_rate = optnull();
    system->target_altitude = optnull();

    system->valves= malloc(sizeof(valve) * num_valves);
    for (unsigned char i=0; i!=num_valves; i++)
        valve_init(&(system->valves[i]));
}

void position_sensor_init(position_sensor* const restrict sensor) {
    sensor->state = optnull();
    sensor->roll = optnull();
    sensor->pitch = optnull();
    sensor->true_heading = optnull();
    sensor->magnetic_heading = optnull();
    sensor->grid_heading = optnull();
    sensor->true_track = optnull();
    sensor->magnetic_track = optnull();
    sensor->grid_track = optnull();
    sensor->longitude = optnull();
    sensor->latitude = optnull();
    sensor->altitude = optnull();
    sensor->ground_elevation = optnull();
    sensor->height_agl = optnull();
    sensor->pitch_rate = optnull();
    sensor->roll_rate = optnull();
    sensor->yaw_rate = optnull();
    sensor->heading_rate = optnull();
    sensor->ground_speed = optnull();
    sensor->vertical_speed = optnull();
    sensor->climb_gradient = optnull();
    sensor->climb_angle = optnull();
    sensor->horizontal_figure_of_merit = optnull();
    sensor->vertical_figure_of_merit = optnull();
    sensor->horizontal_protection_level = optnull();
    sensor->vertical_protection_level = optnull();
}

void radio_init(radio* const restrict radio) {
    radio->active = optnull();
    radio->monitoring = optnull();
    radio->monitoring_standby = optnull();
    radio->transmitting = optnull();
    radio->receiving = optnull();
    radio->squelched = optnull();
    radio->beat_frequency_oscillation = optnull();
    radio->ident = optnull();
    radio->single_sideband = optnull();
    radio->active_frequency = optnull();
    radio->standby_frequency = optnull();
    radio->volume = optnull();
    radio->squelch = optnull();
}

void radio_altimeter_init(radio_altimeter* const restrict radio_altimeter) {
    radio_altimeter->state = optnull();
    radio_altimeter->altitude = optnull();
    radio_altimeter->alert_altitude = optnull();
}

void rotor_init(rotor* const restrict rotor) {
    rotor->rotational_velocity = optnull();
    rotor->blade_angle = optnull();
}

void transponder_init(transponder* const restrict transponder) {
    transponder->mode = optnull();
    transponder->mode_3a_code = optnull();
    transponder->mode_s_code = optnull();
    transponder->flight_id = optnull();
    transponder->replying = optnull();
}

void traffic_system_init(traffic_system* const restrict system) {
    system->mode = optnull();
    system->traffic_advisory = optnull();
    system->resolution_advisory = optnull();
    system->horizontal_resolution_advisory = optnull();
    system->vertical_resolution_advisory = optnull();
}

void spool_init(spool* const restrict spool) {
    spool->n = optnull();
    spool->rotational_velocity = optnull();
}

void valve_init(valve* const restrict valve) {
    valve->position = optnull();
}

void aircraft_record_merge(aircraft_record* const restrict predator, const aircraft_record* const restrict prey) {
    if (predator->aircraft != prey->aircraft) return;

    if (predator->acceleration_lateral.null)
        predator->acceleration_lateral = prey->acceleration_lateral;
    if (predator->acceleration_longitudinal.null)
        predator->acceleration_longitudinal = prey->acceleration_longitudinal;
    if (predator->acceleration_normal.null)
        predator->acceleration_normal = prey->acceleration_normal;
    if (predator->magnetic_variation.null)
        predator->magnetic_variation = prey->magnetic_variation;
    if (predator->grid_convergence.null)
        predator->grid_convergence = prey->grid_convergence;
    if (predator->fuel_totalizer_used.null)
        predator->fuel_totalizer_used = prey->fuel_totalizer_used;
    if (predator->fuel_totalizer_remaining.null)
        predator->fuel_totalizer_remaining = prey->fuel_totalizer_remaining;
    if (predator->fuel_totalizer_economy.null)
        predator->fuel_totalizer_economy = prey->fuel_totalizer_economy;
    if (predator->fuel_totalizer_used_weight.null)
        predator->fuel_totalizer_used_weight = prey->fuel_totalizer_used_weight;
    if (predator->fuel_totalizer_remaining_weight.null)
        predator->fuel_totalizer_remaining_weight = prey->fuel_totalizer_remaining_weight;
    if (predator->fuel_totalizer_economy_weight.null)
        predator->fuel_totalizer_economy_weight = prey->fuel_totalizer_economy_weight;
    if (predator->fuel_totalizer_time_remaining.null)
        predator->fuel_totalizer_time_remaining = prey->fuel_totalizer_time_remaining;
    if (predator->autopilot_active.null)
        predator->autopilot_active = prey->autopilot_active;
    if (predator->autopilot_mode.null)
        predator->autopilot_mode = prey->autopilot_mode;
    if (predator->autopilot_lateral_active_mode.null)
        predator->autopilot_lateral_active_mode = prey->autopilot_lateral_active_mode;
    if (predator->autopilot_lateral_armed_mode.null)
        predator->autopilot_lateral_armed_mode = prey->autopilot_lateral_armed_mode;
    if (predator->autopilot_vertical_active_mode.null)
        predator->autopilot_vertical_active_mode = prey->autopilot_vertical_active_mode;
    if (predator->autopilot_vertical_armed_mode.null)
        predator->autopilot_vertical_armed_mode = prey->autopilot_vertical_armed_mode;
    if (predator->autopilot_altitude_target.null)
        predator->autopilot_altitude_target = prey->autopilot_altitude_target;
    if (predator->autothrottle_active_mode.null)
        predator->autothrottle_active_mode = prey->autothrottle_active_mode;
    if (predator->autothrottle_armed_mode.null)
        predator->autothrottle_armed_mode = prey->autothrottle_armed_mode;
    if (predator->master_warning.null)
        predator->master_warning = prey->master_warning;
    if (predator->master_caution.null)
        predator->master_caution = prey->master_caution;
    if (predator->fire_warning.null)
        predator->fire_warning = prey->fire_warning;
    if (predator->drift_angle.null)
        predator->drift_angle = prey->drift_angle;
    if (predator->wind_direction.null)
        predator->wind_direction = prey->wind_direction;
    if (predator->wind_speed.null)
        predator->wind_speed = prey->wind_speed;
    if (predator->mass.null)
        predator->mass = prey->mass;
    if (predator->center_of_gravity.null)
        predator->center_of_gravity = prey->center_of_gravity;
    if (predator->percent_mac.null)
        predator->percent_mac = prey->percent_mac;

    for (unsigned int i=0; i!=predator->aircraft->num_anti_ice_systems; i++) {
        if (predator->anti_ice_systems[i].active.null)
            predator->anti_ice_systems[i].active = prey->anti_ice_systems[i].active;
        if (predator->anti_ice_systems[i].mode.null)
            predator->anti_ice_systems[i].mode = prey->anti_ice_systems[i].mode;
        if (predator->anti_ice_systems[i].current.null)
            predator->anti_ice_systems[i].current = prey->anti_ice_systems[i].current;
        if (predator->anti_ice_systems[i].fluid_quantity.null)
            predator->anti_ice_systems[i].fluid_quantity = prey->anti_ice_systems[i].fluid_quantity;
        if (predator->anti_ice_systems[i].fluid_flow_rate.null)
            predator->anti_ice_systems[i].fluid_flow_rate = prey->anti_ice_systems[i].fluid_flow_rate;
        if (predator->anti_ice_systems[i].vacuum.null)
            predator->anti_ice_systems[i].vacuum = prey->anti_ice_systems[i].vacuum;
    }

    for (unsigned int i=0; i!=predator->aircraft->num_bleed_air_systems; i++) {
        if (predator->bleed_air_systems[i].active.null)
            predator->bleed_air_systems[i].active = prey->bleed_air_systems[i].active;
        if (predator->bleed_air_systems[i].temperature.null)
            predator->bleed_air_systems[i].temperature = prey->bleed_air_systems[i].temperature;
        if (predator->bleed_air_systems[i].pressure.null)
            predator->bleed_air_systems[i].pressure = prey->bleed_air_systems[i].pressure;
        if (predator->bleed_air_systems[i].valve_position.null)
            predator->bleed_air_systems[i].valve_position = prey->bleed_air_systems[i].valve_position;
    }

    for (unsigned int i=0; i!=predator->aircraft->num_control_surfaces; i++) {
        if (predator->control_surfaces[i].position.null)
            predator->control_surfaces[i].position = prey->control_surfaces[i].position;
        if (predator->control_surfaces[i].trim.null)
            predator->control_surfaces[i].trim = prey->control_surfaces[i].trim;
        if (predator->control_surfaces[i].position_factor.null)
            predator->control_surfaces[i].position_factor = prey->control_surfaces[i].position_factor;
        if (predator->control_surfaces[i].trim_factor.null)
            predator->control_surfaces[i].trim_factor = prey->control_surfaces[i].trim_factor;
    }

    for (unsigned int i=0; i!=predator->aircraft->num_displays; i++) {
        if (predator->displays[i].active.null)
            predator->displays[i].active = prey->displays[i].active;
        if (predator->displays[i].format.null)
            predator->displays[i].format = prey->displays[i].format;
    }

    for (unsigned int i=0; i!=predator->aircraft->num_electrical_systems; i++) {
        if (predator->electrical_systems[i].active.null)
            predator->electrical_systems[i].active = prey->electrical_systems[i].active;
        if (predator->electrical_systems[i].current.null)
            predator->electrical_systems[i].current = prey->electrical_systems[i].current;
        if (predator->electrical_systems[i].potential.null)
            predator->electrical_systems[i].potential = prey->electrical_systems[i].potential;
        if (predator->electrical_systems[i].frequency.null)
            predator->electrical_systems[i].frequency = prey->electrical_systems[i].frequency;
    }

    for (unsigned int e=0; e!=predator->aircraft->num_engines; e++) {
        if (predator->engines[e].fuel_flow.null)
          predator->engines[e].fuel_flow = prey->engines[e].fuel_flow;
        if (predator->engines[e].fuel_pressure.null)
          predator->engines[e].fuel_pressure = prey->engines[e].fuel_pressure;
        if (predator->engines[e].vibration.null)
          predator->engines[e].vibration = prey->engines[e].vibration;
        if (predator->engines[e].thrust_lever_position.null)
          predator->engines[e].thrust_lever_position = prey->engines[e].thrust_lever_position;
        if (predator->engines[e].reverser_position.null)
          predator->engines[e].reverser_position = prey->engines[e].reverser_position;
        if (predator->engines[e].reverser_lever_stowed.null)
            predator->engines[e].reverser_lever_stowed = prey->engines[e].reverser_lever_stowed;
        if (predator->engines[e].throttle_position.null)
          predator->engines[e].throttle_position = prey->engines[e].throttle_position;
        if (predator->engines[e].mixture_lever_position.null)
          predator->engines[e].mixture_lever_position = prey->engines[e].mixture_lever_position;
        if (predator->engines[e].propeller_lever_position.null)
          predator->engines[e].propeller_lever_position = prey->engines[e].propeller_lever_position;
        if (predator->engines[e].magneto_position.null)
          predator->engines[e].magneto_position = prey->engines[e].magneto_position;
        if (predator->engines[e].carburetor_heat_lever_position.null)
          predator->engines[e].carburetor_heat_lever_position = prey->engines[e].carburetor_heat_lever_position;
        if (predator->engines[e].cowl_flap_lever_position.null)
          predator->engines[e].cowl_flap_lever_position = prey->engines[e].cowl_flap_lever_position;
        if (predator->engines[e].altitude_throttle_position.null)
          predator->engines[e].altitude_throttle_position = prey->engines[e].altitude_throttle_position;
        if (predator->engines[e].condition_lever_position.null)
          predator->engines[e].condition_lever_position = prey->engines[e].condition_lever_position;
        if (predator->engines[e].beta_position.null)
          predator->engines[e].beta_position = prey->engines[e].beta_position;
        if (predator->engines[e].ignition_mode.null)
          predator->engines[e].ignition_mode = prey->engines[e].ignition_mode;
        if (predator->engines[e].autothrottle_active.null)
          predator->engines[e].autothrottle_active = prey->engines[e].autothrottle_active;
        if (predator->engines[e].fuel_source.null)
          predator->engines[e].fuel_source = prey->engines[e].fuel_source;
        if (predator->engines[e].reverser_opened.null)
            predator->engines[e].reverser_opened = prey->engines[e].reverser_opened;
        if (predator->engines[e].thrust.null)
          predator->engines[e].thrust = prey->engines[e].thrust;
        if (predator->engines[e].torque.null)
          predator->engines[e].torque = prey->engines[e].torque;
        if (predator->engines[e].torque_factor.null)
            predator->engines[e].torque_factor = prey->engines[e].torque_factor;
        if (predator->engines[e].autofeather_armed.null)
          predator->engines[e].autofeather_armed = prey->engines[e].autofeather_armed;
        if (predator->engines[e].manifold_pressure.null)
          predator->engines[e].manifold_pressure = prey->engines[e].manifold_pressure;
        if (predator->engines[e].percent_thrust.null)
          predator->engines[e].percent_thrust = prey->engines[e].percent_thrust;
        if (predator->engines[e].thrust.null)
          predator->engines[e].thrust = prey->engines[e].thrust;
        if (predator->engines[e].percent_power.null)
          predator->engines[e].percent_power = prey->engines[e].percent_power;
        if (predator->engines[e].power.null)
          predator->engines[e].power = prey->engines[e].power;
        if (predator->engines[e].percent_power.null)
          predator->engines[e].percent_power = prey->engines[e].percent_power;
        if (predator->engines[e].engine_pressure_ratio.null)
          predator->engines[e].engine_pressure_ratio = prey->engines[e].engine_pressure_ratio;
        if (predator->engines[e].exhaust_gas_temperature.null)
          predator->engines[e].exhaust_gas_temperature = prey->engines[e].exhaust_gas_temperature;
        if (predator->engines[e].interstage_turbine_temperature.null)
          predator->engines[e].interstage_turbine_temperature = prey->engines[e].interstage_turbine_temperature;
        if (predator->engines[e].turbine_inlet_temperature.null)
          predator->engines[e].turbine_inlet_temperature = prey->engines[e].turbine_inlet_temperature;
        if (predator->engines[e].oil_pressure.null)
          predator->engines[e].oil_pressure = prey->engines[e].oil_pressure;
        if (predator->engines[e].oil_temperature.null)
          predator->engines[e].oil_temperature = prey->engines[e].oil_temperature;

        for (unsigned int c=0; c!=predator->aircraft->cylinders_per_engine[e]; c++) {
            if (predator->engines[e].cylinders[c].cylinder_head_temperature.null)
                predator->engines[e].cylinders[c].cylinder_head_temperature = prey->engines[e].cylinders[c].cylinder_head_temperature;
            if (predator->engines[e].cylinders[c].exhaust_gas_temperature.null)
                predator->engines[e].cylinders[c].exhaust_gas_temperature = prey->engines[e].cylinders[c].exhaust_gas_temperature;
        }

        for (unsigned int p=0; p!=predator->aircraft->propellers_per_engine[e]; p++) {
            if (predator->engines[e].propellers[p].rotational_velocity.null)
                predator->engines[e].propellers[p].rotational_velocity = prey->engines[e].propellers[p].rotational_velocity;
        }

        for (unsigned int s=0; s!=predator->aircraft->spools_per_engine[e]; s++) {
            if (predator->engines[e].spools[s].n.null)
                predator->engines[e].spools[s].n = prey->engines[e].spools[s].n;
            if (predator->engines[e].spools[s].rotational_velocity.null)
                predator->engines[e].spools[s].rotational_velocity = prey->engines[e].spools[s].rotational_velocity;
        }
    }

    for (unsigned int s=0; s!=predator->aircraft->num_flight_control_sets; s++) {
        for (unsigned int c=0; c!=predator->aircraft->num_flight_controls; c++) {
            if (predator->flight_controls[s][c].position.null)
                predator->flight_controls[s][c].position = prey->flight_controls[s][c].position;
            if (predator->flight_controls[s][c].shaker.null)
                predator->flight_controls[s][c].shaker = prey->flight_controls[s][c].shaker;
            if (predator->flight_controls[s][c].pusher.null)
                predator->flight_controls[s][c].pusher = prey->flight_controls[s][c].pusher;
        }
    }

    for (unsigned int i=0; i!=predator->aircraft->num_fuel_tanks; i++) {
        if (predator->fuel_tanks[i].quantity.null)
            predator->fuel_tanks[i].quantity = prey->fuel_tanks[i].quantity;
        if (predator->fuel_tanks[i].quantity_weight.null)
            predator->fuel_tanks[i].quantity_weight = prey->fuel_tanks[i].quantity_weight;
        if (predator->fuel_tanks[i].temperature.null)
            predator->fuel_tanks[i].temperature = prey->fuel_tanks[i].temperature;
    }

    for (unsigned int i=0; i!=predator->aircraft->num_hydraulic_systems; i++) {
        if (predator->hydraulic_systems[i].pressure.null)
            predator->hydraulic_systems[i].pressure = prey->hydraulic_systems[i].pressure;
        if (predator->hydraulic_systems[i].temperature.null)
            predator->hydraulic_systems[i].temperature = prey->hydraulic_systems[i].temperature;
        if (predator->hydraulic_systems[i].fluid_quantity.null)
            predator->hydraulic_systems[i].fluid_quantity = prey->hydraulic_systems[i].fluid_quantity;
        if (predator->hydraulic_systems[i].fluid_quantity_percent.null)
            predator->hydraulic_systems[i].fluid_quantity_percent = prey->hydraulic_systems[i].fluid_quantity_percent;
    }

    for (unsigned int i=0; i!=predator->aircraft->num_ice_detection_systems; i++) {
        if (predator->ice_detection_systems[i].ice_detected.null)
            predator->ice_detection_systems[i].ice_detected = prey->ice_detection_systems[i].ice_detected;
    }

    for (unsigned int i=0; i!=predator->aircraft->num_instrument_sets; i++) {
        if (predator->instrument_sets[i].flight_director.null)
            predator->instrument_sets[i].flight_director = prey->instrument_sets[i].flight_director;
        if (predator->instrument_sets[i].ins.null)
            predator->instrument_sets[i].ins = prey->instrument_sets[i].ins;
        if (predator->instrument_sets[i].gps.null)
            predator->instrument_sets[i].gps = prey->instrument_sets[i].gps;
        if (predator->instrument_sets[i].adahrs.null)
            predator->instrument_sets[i].adahrs = prey->instrument_sets[i].adahrs;
        if (predator->instrument_sets[i].fms.null)
            predator->instrument_sets[i].fms = prey->instrument_sets[i].fms;
        if (predator->instrument_sets[i].nav_radio.null)
            predator->instrument_sets[i].nav_radio = prey->instrument_sets[i].nav_radio;
        if (predator->instrument_sets[i].adf.null)
            predator->instrument_sets[i].adf = prey->instrument_sets[i].adf;
        if (predator->instrument_sets[i].pitot_static_system.null)
            predator->instrument_sets[i].pitot_static_system = prey->instrument_sets[i].pitot_static_system;
        if (predator->instrument_sets[i].cdi_source.null)
            predator->instrument_sets[i].cdi_source = prey->instrument_sets[i].cdi_source;
        if (predator->instrument_sets[i].obs.null)
            predator->instrument_sets[i].obs = prey->instrument_sets[i].obs;
        if (predator->instrument_sets[i].course.null)
            predator->instrument_sets[i].course = prey->instrument_sets[i].course;
        if (predator->instrument_sets[i].altitude_bug.null)
            predator->instrument_sets[i].altitude_bug = prey->instrument_sets[i].altitude_bug;
        if (predator->instrument_sets[i].decision_height.null)
            predator->instrument_sets[i].decision_height = prey->instrument_sets[i].decision_height;
        if (predator->instrument_sets[i].indicated_airspeed_bug.null)
            predator->instrument_sets[i].indicated_airspeed_bug = prey->instrument_sets[i].indicated_airspeed_bug;
        if (predator->instrument_sets[i].mach_bug.null)
            predator->instrument_sets[i].mach_bug = prey->instrument_sets[i].mach_bug;
        if (predator->instrument_sets[i].vertical_speed_bug.null)
            predator->instrument_sets[i].vertical_speed_bug = prey->instrument_sets[i].vertical_speed_bug;
        if (predator->instrument_sets[i].flight_path_angle_bug.null)
            predator->instrument_sets[i].flight_path_angle_bug = prey->instrument_sets[i].flight_path_angle_bug;
        if (predator->instrument_sets[i].heading_bug.null)
            predator->instrument_sets[i].heading_bug = prey->instrument_sets[i].heading_bug;
        if (predator->instrument_sets[i].track_bug.null)
            predator->instrument_sets[i].track_bug = prey->instrument_sets[i].track_bug;
        if (predator->instrument_sets[i].indicated_altitude.null)
            predator->instrument_sets[i].indicated_altitude = prey->instrument_sets[i].indicated_altitude;
        if (predator->instrument_sets[i].altimeter_setting.null)
            predator->instrument_sets[i].altimeter_setting = prey->instrument_sets[i].altimeter_setting;
        if (predator->instrument_sets[i].flight_director_active.null)
            predator->instrument_sets[i].flight_director_active = prey->instrument_sets[i].flight_director_active;
        if (predator->instrument_sets[i].flight_director_pitch.null)
            predator->instrument_sets[i].flight_director_pitch = prey->instrument_sets[i].flight_director_pitch;
        if (predator->instrument_sets[i].flight_director_roll.null)
            predator->instrument_sets[i].flight_director_roll = prey->instrument_sets[i].flight_director_roll;
    }

    for (unsigned int truck=0; truck!=predator->aircraft->num_trucks; truck++) {
        if (predator->trucks[truck].door_state.null)
            predator->trucks[truck].door_state = prey->trucks[truck].door_state;
        if (predator->trucks[truck].weight_on_wheels.null)
            predator->trucks[truck].weight_on_wheels = prey->trucks[truck].weight_on_wheels;

        for (unsigned int tire=0; tire!=predator->aircraft->tires_per_truck[truck]; tire++) {
            if (predator->trucks[truck].tires[tire].air_pressure.null)
                predator->trucks[truck].tires[tire].air_pressure = prey->trucks[truck].tires[tire].air_pressure;
            if (predator->trucks[truck].tires[tire].brake_temperature.null)
                predator->trucks[truck].tires[tire].brake_temperature = prey->trucks[truck].tires[tire].brake_temperature;
        }
    }

    for (unsigned int i=0; i!=predator->aircraft->num_navigation_systems; i++) {
        if (predator->navigation_systems[i].active.null)
            predator->navigation_systems[i].active = prey->navigation_systems[i].active;
        if (predator->navigation_systems[i].mode.null)
            predator->navigation_systems[i].mode = prey->navigation_systems[i].mode;
        if (predator->navigation_systems[i].desired_track.null)
            predator->navigation_systems[i].desired_track = prey->navigation_systems[i].desired_track;
        if (predator->navigation_systems[i].course.null)
            predator->navigation_systems[i].course = prey->navigation_systems[i].course;
        if (predator->navigation_systems[i].bearing.null)
            predator->navigation_systems[i].bearing = prey->navigation_systems[i].bearing;
        if (predator->navigation_systems[i].course_deviation.null)
            predator->navigation_systems[i].course_deviation = prey->navigation_systems[i].course_deviation;
        if (predator->navigation_systems[i].lateral_deviation.null)
            predator->navigation_systems[i].lateral_deviation = prey->navigation_systems[i].lateral_deviation;
        if (predator->navigation_systems[i].vertical_deviation.null)
            predator->navigation_systems[i].vertical_deviation = prey->navigation_systems[i].vertical_deviation;
        if (predator->navigation_systems[i].lateral_deviation_factor.null)
            predator->navigation_systems[i].lateral_deviation_factor = prey->navigation_systems[i].lateral_deviation_factor;
        if (predator->navigation_systems[i].vertical_deviation_factor.null)
            predator->navigation_systems[i].vertical_deviation_factor = prey->navigation_systems[i].vertical_deviation_factor;
        if (predator->navigation_systems[i].distance_to_waypoint.null)
            predator->navigation_systems[i].distance_to_waypoint = prey->navigation_systems[i].distance_to_waypoint;
        if (predator->navigation_systems[i].radio.null)
            predator->navigation_systems[i].radio = prey->navigation_systems[i].radio;
        if (predator->navigation_systems[i].active_waypoint.null)
            predator->navigation_systems[i].active_waypoint = opts_copy(prey->navigation_systems[i].active_waypoint);
    }

    for (unsigned int i=0; i!=predator->aircraft->num_marker_beacons; i++) {
        if (predator->marker_beacons[i].outer.null)
            predator->marker_beacons[i].outer = prey->marker_beacons[i].outer;
        if (predator->marker_beacons[i].middle.null)
            predator->marker_beacons[i].middle = prey->marker_beacons[i].middle;
        if (predator->marker_beacons[i].inner.null)
            predator->marker_beacons[i].inner = prey->marker_beacons[i].inner;
    }

    for (unsigned int i=0; i!=predator->aircraft->num_packs; i++) {
        if (predator->packs[i].active.null)
            predator->packs[i].active = prey->packs[i].active;
        if (predator->packs[i].air_pressure.null)
            predator->packs[i].air_pressure = prey->packs[i].air_pressure;
        if (predator->packs[i].air_temperature.null)
            predator->packs[i].air_temperature = prey->packs[i].air_temperature;
    }

    for (unsigned int i=0; i!=predator->aircraft->num_pitot_static_systems; i++) {
        if (predator->pitot_static_systems[i].static_air_temperature.null)
            predator->pitot_static_systems[i].static_air_temperature = prey->pitot_static_systems[i].static_air_temperature;
        if (predator->pitot_static_systems[i].total_air_temperature.null)
            predator->pitot_static_systems[i].total_air_temperature = prey->pitot_static_systems[i].total_air_temperature;
        if (predator->pitot_static_systems[i].temperature_deviation.null)
            predator->pitot_static_systems[i].temperature_deviation = prey->pitot_static_systems[i].temperature_deviation;
        if (predator->pitot_static_systems[i].air_pressure.null)
            predator->pitot_static_systems[i].air_pressure = prey->pitot_static_systems[i].air_pressure;
        if (predator->pitot_static_systems[i].air_density.null)
            predator->pitot_static_systems[i].air_density = prey->pitot_static_systems[i].air_density;
        if (predator->pitot_static_systems[i].pressure_altitude.null)
            predator->pitot_static_systems[i].pressure_altitude = prey->pitot_static_systems[i].pressure_altitude;
        if (predator->pitot_static_systems[i].density_altitude.null)
            predator->pitot_static_systems[i].density_altitude = prey->pitot_static_systems[i].density_altitude;
        if (predator->pitot_static_systems[i].indicated_airspeed.null)
            predator->pitot_static_systems[i].indicated_airspeed = prey->pitot_static_systems[i].indicated_airspeed;
        if (predator->pitot_static_systems[i].calibrated_airspeed.null)
            predator->pitot_static_systems[i].calibrated_airspeed = prey->pitot_static_systems[i].calibrated_airspeed;
        if (predator->pitot_static_systems[i].true_airpseed.null)
            predator->pitot_static_systems[i].true_airpseed = prey->pitot_static_systems[i].true_airpseed;
        if (predator->pitot_static_systems[i].speed_of_sound.null)
            predator->pitot_static_systems[i].speed_of_sound = prey->pitot_static_systems[i].speed_of_sound;
        if (predator->pitot_static_systems[i].mach.null)
            predator->pitot_static_systems[i].mach = prey->pitot_static_systems[i].mach;
        if (predator->pitot_static_systems[i].vertical_speed.null)
            predator->pitot_static_systems[i].vertical_speed = prey->pitot_static_systems[i].vertical_speed;
        if (predator->pitot_static_systems[i].angle_of_attack.null)
            predator->pitot_static_systems[i].angle_of_attack = prey->pitot_static_systems[i].angle_of_attack;
        if (predator->pitot_static_systems[i].angle_of_sideslip.null)
            predator->pitot_static_systems[i].angle_of_sideslip = prey->pitot_static_systems[i].angle_of_sideslip;
    }

    for (unsigned int i=0; i!=predator->aircraft->num_pneumatic_systems; i++) {
        if (predator->pneumatic_systems[i].pressure.null)
            predator->pneumatic_systems[i].pressure = prey->pneumatic_systems[i].pressure;
    }

    for (unsigned int i=0; i!=predator->aircraft->num_pressurization_systems; i++) {
        if (predator->pressurization_systems[i].mode.null)
            predator->pressurization_systems[i].mode = prey->pressurization_systems[i].mode;
        if (predator->pressurization_systems[i].differential_pressure.null)
            predator->pressurization_systems[i].differential_pressure = prey->pressurization_systems[i].differential_pressure;
        if (predator->pressurization_systems[i].cabin_altitude.null)
            predator->pressurization_systems[i].cabin_altitude = prey->pressurization_systems[i].cabin_altitude;
        if (predator->pressurization_systems[i].cabin_rate.null)
            predator->pressurization_systems[i].cabin_rate = prey->pressurization_systems[i].cabin_rate;
        if (predator->pressurization_systems[i].target_altitude.null)
            predator->pressurization_systems[i].target_altitude = prey->pressurization_systems[i].target_altitude;

        for (unsigned int valve=0; valve!=predator->aircraft->valves_per_pressurization_system[i]; valve++) {
            if (predator->pressurization_systems[i].valves[valve].position.null)
                predator->pressurization_systems[i].valves[valve].position = prey->pressurization_systems[i].valves[valve].position;
        }
    }

    for (unsigned int i=0; i!=predator->aircraft->num_position_sensors; i++) {
        if (predator->position_sensors[i].state.null)
            predator->position_sensors[i].state = prey->position_sensors[i].state;
        if (predator->position_sensors[i].roll.null)
            predator->position_sensors[i].roll = prey->position_sensors[i].roll;
        if (predator->position_sensors[i].pitch.null)
            predator->position_sensors[i].pitch = prey->position_sensors[i].pitch;
        if (predator->position_sensors[i].true_heading.null)
            predator->position_sensors[i].true_heading = prey->position_sensors[i].true_heading;
        if (predator->position_sensors[i].magnetic_heading.null)
            predator->position_sensors[i].magnetic_heading = prey->position_sensors[i].magnetic_heading;
        if (predator->position_sensors[i].grid_heading.null)
            predator->position_sensors[i].grid_heading = prey->position_sensors[i].grid_heading;
        if (predator->position_sensors[i].true_track.null)
            predator->position_sensors[i].true_track = prey->position_sensors[i].true_track;
        if (predator->position_sensors[i].magnetic_track.null)
            predator->position_sensors[i].magnetic_track = prey->position_sensors[i].magnetic_track;
        if (predator->position_sensors[i].grid_track.null)
            predator->position_sensors[i].grid_track = prey->position_sensors[i].grid_track;
        if (predator->position_sensors[i].longitude.null)
            predator->position_sensors[i].longitude = prey->position_sensors[i].longitude;
        if (predator->position_sensors[i].latitude.null)
            predator->position_sensors[i].latitude = prey->position_sensors[i].latitude;
        if (predator->position_sensors[i].altitude.null)
            predator->position_sensors[i].altitude = prey->position_sensors[i].altitude;
        if (predator->position_sensors[i].ground_elevation.null)
            predator->position_sensors[i].ground_elevation = prey->position_sensors[i].ground_elevation;
        if (predator->position_sensors[i].height_agl.null)
            predator->position_sensors[i].height_agl = prey->position_sensors[i].height_agl;
        if (predator->position_sensors[i].pitch_rate.null)
            predator->position_sensors[i].pitch_rate = prey->position_sensors[i].pitch_rate;
        if (predator->position_sensors[i].roll_rate.null)
            predator->position_sensors[i].roll_rate = prey->position_sensors[i].roll_rate;
        if (predator->position_sensors[i].yaw_rate.null)
            predator->position_sensors[i].yaw_rate = prey->position_sensors[i].yaw_rate;
        if (predator->position_sensors[i].heading_rate.null)
            predator->position_sensors[i].heading_rate = prey->position_sensors[i].heading_rate;
        if (predator->position_sensors[i].ground_speed.null)
            predator->position_sensors[i].ground_speed = prey->position_sensors[i].ground_speed;
        if (predator->position_sensors[i].vertical_speed.null)
            predator->position_sensors[i].vertical_speed = prey->position_sensors[i].vertical_speed;
        if (predator->position_sensors[i].climb_gradient.null)
            predator->position_sensors[i].climb_gradient = prey->position_sensors[i].climb_gradient;
        if (predator->position_sensors[i].climb_angle.null)
            predator->position_sensors[i].climb_angle = prey->position_sensors[i].climb_angle;
        if (predator->position_sensors[i].horizontal_figure_of_merit.null)
            predator->position_sensors[i].horizontal_figure_of_merit = prey->position_sensors[i].horizontal_figure_of_merit;
        if (predator->position_sensors[i].vertical_figure_of_merit.null)
            predator->position_sensors[i].vertical_figure_of_merit = prey->position_sensors[i].vertical_figure_of_merit;
        if (predator->position_sensors[i].horizontal_protection_level.null)
            predator->position_sensors[i].horizontal_protection_level = prey->position_sensors[i].horizontal_protection_level;
        if (predator->position_sensors[i].vertical_protection_level.null)
            predator->position_sensors[i].vertical_protection_level = prey->position_sensors[i].vertical_protection_level;
    }

    for (unsigned int i=0; i!=predator->aircraft->num_radios; i++) {
        if (predator->radios[i].active.null)
            predator->radios[i].active = prey->radios[i].active;
        if (predator->radios[i].monitoring.null)
            predator->radios[i].monitoring = prey->radios[i].monitoring;
        if (predator->radios[i].monitoring_standby.null)
            predator->radios[i].monitoring_standby = prey->radios[i].monitoring_standby;
        if (predator->radios[i].transmitting.null)
            predator->radios[i].transmitting = prey->radios[i].transmitting;
        if (predator->radios[i].receiving.null)
            predator->radios[i].receiving = prey->radios[i].receiving;
        if (predator->radios[i].squelched.null)
            predator->radios[i].squelched = prey->radios[i].squelched;
        if (predator->radios[i].beat_frequency_oscillation.null)
            predator->radios[i].beat_frequency_oscillation = prey->radios[i].beat_frequency_oscillation;
        if (predator->radios[i].ident.null)
            predator->radios[i].ident = prey->radios[i].ident;
        if (predator->radios[i].single_sideband.null)
            predator->radios[i].single_sideband = prey->radios[i].single_sideband;
        if (predator->radios[i].active_frequency.null)
            predator->radios[i].active_frequency = prey->radios[i].active_frequency;
        if (predator->radios[i].standby_frequency.null)
            predator->radios[i].standby_frequency = prey->radios[i].standby_frequency;
        if (predator->radios[i].volume.null)
            predator->radios[i].volume = prey->radios[i].volume;
        if (predator->radios[i].squelched.null)
            predator->radios[i].squelched = prey->radios[i].squelched;
    }

    for (unsigned int i=0; i!=predator->aircraft->num_radio_altimeters; i++) {
        if (predator->radio_altimeters[i].state.null)
            predator->radio_altimeters[i].state = prey->radio_altimeters[i].state;
        if (predator->radio_altimeters[i].altitude.null)
            predator->radio_altimeters[i].altitude = prey->radio_altimeters[i].altitude;
        if (predator->radio_altimeters[i].alert_altitude.null)
            predator->radio_altimeters[i].alert_altitude = prey->radio_altimeters[i].alert_altitude;
    }

    for (unsigned int i=0; i!=predator->aircraft->num_rotors; i++) {
        if (predator->rotors[i].rotational_velocity.null)
            predator->rotors[i].rotational_velocity = prey->rotors[i].rotational_velocity;
        if (predator->rotors[i].blade_angle.null)
            predator->rotors[i].blade_angle = prey->rotors[i].blade_angle;
    }

    for (unsigned int i=0; i!=predator->aircraft->num_transponders; i++) {
        if (predator->transponders[i].mode.null)
            predator->transponders[i].mode = prey->transponders[i].mode;
        if (predator->transponders[i].mode_3a_code.null)
            predator->transponders[i].mode_3a_code = prey->transponders[i].mode_3a_code;
        if (predator->transponders[i].mode_s_code.null)
            predator->transponders[i].mode_s_code = prey->transponders[i].mode_s_code;
        if (predator->transponders[i].flight_id.null)
            predator->transponders[i].flight_id = prey->transponders[i].flight_id;
        if (predator->transponders[i].replying.null)
            predator->transponders[i].replying = prey->transponders[i].replying;
    }

    for (unsigned int i=0; i!=predator->aircraft->num_traffic_systems; i++) {
        if (predator->traffic_systems[i].mode.null)
            predator->traffic_systems[i].mode = prey->traffic_systems[i].mode;
        if (predator->traffic_systems[i].traffic_advisory.null)
            predator->traffic_systems[i].traffic_advisory = prey->traffic_systems[i].traffic_advisory;
        if (predator->traffic_systems[i].resolution_advisory.null)
            predator->traffic_systems[i].resolution_advisory = prey->traffic_systems[i].resolution_advisory;
        if (predator->traffic_systems[i].horizontal_resolution_advisory.null)
            predator->traffic_systems[i].horizontal_resolution_advisory = prey->traffic_systems[i].horizontal_resolution_advisory;
        if (predator->traffic_systems[i].vertical_resolution_advisory.null)
            predator->traffic_systems[i].vertical_resolution_advisory = prey->traffic_systems[i].vertical_resolution_advisory;
    }
}
