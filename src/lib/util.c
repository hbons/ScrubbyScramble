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


#include "palettes.h"
#include "tileset.h"
#include "util.h"


void util_system_reset(void)
{
    __asm__("jmp [0xFFFC]");
}


u8 util_rand_max(u8 max)
{
    return rand() % max;
}


void util_clear_bkg(void)
{
    fill_bkg_rect(0, 0, DEVICE_SCREEN_WIDTH, DEVICE_SCREEN_HEIGHT, TILE_EMPTY);
}


void util_hide_sprites(void)
{
    hide_sprites_range(0, MAX_HARDWARE_SPRITES);
}
