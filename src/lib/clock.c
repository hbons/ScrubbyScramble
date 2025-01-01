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

#pragma bank 0


#include "clock.h"


struct Clock SYS_CLOCK = { 0, 0, 0 };

u8 CLOCK_FRAME = 1;
bool CLOCK_EVEN = true;
bool CLOCK_ODD  = false;


void clock_update(void)
{
    SYS_CLOCK.ticks += 1;
    clock_update_ticks();

    CLOCK_EVEN = !CLOCK_EVEN;
    CLOCK_ODD  = !CLOCK_ODD;

    if (CLOCK_FRAME == CLOCK_FPS) {
        CLOCK_FRAME = 1;
        SYS_CLOCK.seconds += 1;

        if (SYS_CLOCK.seconds == 60) {
            SYS_CLOCK.minutes += 1;
            SYS_CLOCK.seconds = 0;
        }

        if (SYS_CLOCK.minutes == 60) {
            SYS_CLOCK.hours += 1;
            SYS_CLOCK.minutes = 0;
        }

    } else {
        CLOCK_FRAME += 1;
    }
}


bool CLOCK_TICK_4;
bool CLOCK_TICK_8;
bool CLOCK_TICK_16;
bool CLOCK_TICK_32;
bool CLOCK_TICK_64;

bool CLOCK_INTERVAL_4;
bool CLOCK_INTERVAL_8;
bool CLOCK_INTERVAL_16;
bool CLOCK_INTERVAL_32;
bool CLOCK_INTERVAL_64;

// Alternates true/false in intervals of n frames
void clock_update_ticks(void)
{
    CLOCK_TICK_4  = false;
    CLOCK_TICK_8  = false;
    CLOCK_TICK_16 = false;
    CLOCK_TICK_32 = false;
    CLOCK_TICK_64 = false;

    if (SYS_CLOCK.ticks % 4 == 0) {
        CLOCK_TICK_4 = true;
        CLOCK_INTERVAL_4 ^= 1;
    }

    if (SYS_CLOCK.ticks % 8 == 0) {
        CLOCK_TICK_8 = true;
        CLOCK_INTERVAL_8 ^= 1;
    }

    if (SYS_CLOCK.ticks % 16 == 0) {
        CLOCK_TICK_16 = true;
        CLOCK_INTERVAL_16 ^= 1;
    }

    if (SYS_CLOCK.ticks % 32 == 0) {
        CLOCK_TICK_32 = true;
        CLOCK_INTERVAL_32 ^= 1;
    }

    if (SYS_CLOCK.ticks % 64 == 0) {
        CLOCK_TICK_64 = true;
        CLOCK_INTERVAL_64 ^= 1;
    }
}
