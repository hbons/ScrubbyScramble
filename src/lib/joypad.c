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


#include "joypad.h"


static joypads_t prev_joypads;
static joypads_t joypads;

void joypad_init_multi(u8 n_pads)
{
    joypad_init(n_pads, &joypads);
}


void joypad_update(void)
{
    prev_joypads = joypads;
    joypad_ex(&joypads);
}


bool joypad_changed(u8 pad)
{
    u8 prev_pad = prev_joypads.joypads[pad];
    pad = joypads.joypads[pad];

    return (pad != prev_pad);
}


bool joypad_button_down(u8 pad, u8 button)
{
    pad = joypads.joypads[pad];
    return (pad & button);
}

bool joypad_button_up(u8 pad, u8 button)
{
    pad = joypads.joypads[pad];
    return !(pad & button);
}


bool joypad_button_pressed(u8 pad, u8 button)
{
    u8 prev_pad = prev_joypads.joypads[pad];
    pad = joypads.joypads[pad];

    return !(prev_pad & button) && (pad & button);
}

bool joypad_button_released(u8 pad, u8 button)
{
    u8 prev_pad = prev_joypads.joypads[pad];
    pad = joypads.joypads[pad];

    return (prev_pad & button) && !(pad & button);
}
