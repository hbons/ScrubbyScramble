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


#include "colors.h"
#include "palettes.h"


const palette_color_t P_CLEAR[4] = {
    C_CLEAR, C_CLEAR, C_CLEAR, C_CLEAR };

const palette_color_t P_FONT[4] = {
    C_COMMON, C_ORANGE_4, C_ORANGE_4, C_ORANGE_4 };


void palettes_init_bkg(const palette_color_t *p1, const palette_color_t *p2,
                       const palette_color_t *p3, const palette_color_t *p4)
{
    set_bkg_palette(S_PALETTE_1, 1, p1);
    set_bkg_palette(S_PALETTE_2, 1, p2);
    set_bkg_palette(S_PALETTE_3, 1, p3);
    set_bkg_palette(S_PALETTE_4, 1, p4);
}

void palettes_init_sprite(const palette_color_t *p1, const palette_color_t *p2,
                          const palette_color_t *p3, const palette_color_t *p4)
{
    set_sprite_palette(S_PALETTE_1, 1, p1);
    set_sprite_palette(S_PALETTE_2, 1, p2);
    set_sprite_palette(S_PALETTE_3, 1, p3);
    set_sprite_palette(S_PALETTE_4, 1, p4);
}


void palettes_clear(void)
{
    palettes_clear_bkg();
    palettes_clear_sprite();
}

void palettes_clear_bkg(void)
{
    for (u8 i = 0; i != N_BKG_PALETTES; i++)
        set_bkg_palette(S_PALETTE_1 + i, 1, P_CLEAR);
}

void palettes_clear_sprite(void)
{
    for (u8 i = 0; i != N_SPR_PALETTES; i++)
        set_sprite_palette(S_PALETTE_1 + i, 1, P_CLEAR);
}
