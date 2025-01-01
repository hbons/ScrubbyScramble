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


#define J_PAD_1 0
#define J_PAD_2 1
#define J_PAD_3 2
#define J_PAD_4 3

void joypad_init_multi(u8 n_pads);
void joypad_update(void);

bool joypad_changed(u8 pad);
bool joypad_button_down(u8 pad, u8 button);
bool joypad_button_up(u8 pad, u8 button);
bool joypad_button_pressed(u8 pad, u8 button);
bool joypad_button_released(u8 pad, u8 button);
