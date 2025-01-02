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

#pragma bank 1


#include "lib/extensions.h"
#include "lib/palettes.h"
#include "lib/tileset.h"

#include "background.skyline.h"


static u8 TILE_BKG_0;
u8 TILE_BKG_0_lamp;

const u8 lamp_map[17][2] = {
    {  0,  2 }, // Hood
    {  1,  3 },
    {  4,  6 },
    {  5,  7 },
    {  8, 10 },
    {  9, 11 },
    { 13, 15 }, // Pole
    { 13, 15 },
    { 13, 15 },
    { 13, 15 },
    { 13, 15 },
    { 13, 15 },
    { 16, 18 }, // Base
    { 17, 19 },
    { 17, 19 },
    { 17, 19 },
    { 17, 19 }
};


#define LAMP_X 5
#define LAMP_Y 8

void background_draw_lamp(void)
{
    TILE_BKG_0 = TILE_BKG_0_lamp;

    for (int row = 0; row != 16; row++)
        for (u8 col = 0; col != 2; col++)
            set_bkg_tile_xy(LAMP_X + col, LAMP_Y + row, TILE_BKG(lamp_map[row][col]));

    // Decorations
    set_bkg_tile_xy(LAMP_X - 1, LAMP_Y + 5, TILE_BKG(12));
    set_bkg_tile_xy(LAMP_X + 2, LAMP_Y + 5, TILE_BKG(14));

    fill_attr_rect(LAMP_X, LAMP_Y,     2, 16, S_PALETTE_3);
    fill_attr_rect(LAMP_X, LAMP_Y + 2, 2,  2, S_PALETTE_2); // Light
}
