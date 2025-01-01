//  Copyright (C) 2024  Hylke Bons (hylke@planetpeanut.studio)
//
//  This program is free software: you can redistribute it and/or modify
//  it under the terms of the GNU General Public License as published by
//  the Free Software Foundation, either version 3 of the License, or
//  (at your option) any later version.
//
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
//  GNU General Public License for more details.


#include "headers.h"


struct Clock {
    u8 hours;
    u8 minutes;
    u8 seconds;

    u8 ticks; // Fine to overflow
};

extern struct Clock SYS_CLOCK;


#define CLOCK_FPS 60 // 59.7 but close enough
extern u8 CLOCK_FRAME; // Range: 1-60 inclusive
extern bool CLOCK_EVEN;
extern bool CLOCK_ODD;


extern bool CLOCK_TICK_4;  //   66ms
extern bool CLOCK_TICK_8;  //  132ms
extern bool CLOCK_TICK_16; //  264ms
extern bool CLOCK_TICK_32; //  528ms
extern bool CLOCK_TICK_64; // 1056ms

extern bool CLOCK_INTERVAL_4;  //   66ms
extern bool CLOCK_INTERVAL_8;  //  132ms
extern bool CLOCK_INTERVAL_16; //  264ms
extern bool CLOCK_INTERVAL_32; //  528ms
extern bool CLOCK_INTERVAL_64; // 1056ms


void clock_init(u8 hours, u8 minutes, u8 seconds);
void clock_update(void);
void clock_update_ticks(void);
