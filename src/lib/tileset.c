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


#include "tileset.h"


static u8 sprite_ptr;
static u8 bkg_ptr;

void tileset_init(void)
{
    // tileset_clear_all();

    sprite_ptr = 0x00;
    bkg_ptr = 0x01; // 0x00 is reserved for the empty tile
}


u8 tileset_init_sprite_tiles(u8 count, const u8* tiles)
{
    u8 prev_ptr = sprite_ptr;
    set_sprite_data(sprite_ptr, count, tiles);
    sprite_ptr += count;

    return prev_ptr;
}


u8 tileset_init_bkg_tiles(u8 count, const u8* tiles)
{
    u8 prev_ptr = bkg_ptr;
    set_bkg_data(bkg_ptr, count, tiles);
    bkg_ptr += count;

    return prev_ptr;
}


const u8 empty_data[16] = { 0x00 };

void tileset_clear_all(void)
{
    tileset_clear_bkg();
    tileset_clear_sprite();
}


void tileset_clear_bkg(void)
{
    set_bkg_data(0x00, 128, empty_data);
}


void tileset_clear_sprite(void)
{
    set_sprite_data(0x00, 128, empty_data);
}
