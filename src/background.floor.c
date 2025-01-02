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

#include "background.floor.h"


static u8 TILE_BKG_0;
u8 TILE_BKG_0_floor;


#define PAVEMENT_COL 7
#define FLOOR_COL 0
#define FLOOR_ROW 24

void background_draw_floor(void)
{
    TILE_BKG_0 = TILE_BKG_0_floor;

    // Fences
    for (u8 col = 0; col != 4; col++)
        for (int row = 0; row != 4; row++) {
            u8 tile = TILE_BKG(row + 2);
            set_bkg_tile_xy(col,      FLOOR_ROW - 1 - row, tile); // Left fence
            set_bkg_tile_xy(col + 28, FLOOR_ROW - 1 - row, tile); // Right fence
        }

    // Grass
    background_draw_grass(4, FLOOR_ROW - 1, 27, FLOOR_ROW - 1);

    // Floor
    for (u8 i = 0; i != 32; i++)
        set_bkg_tile_xy(FLOOR_COL + i, FLOOR_ROW, TILE_BKG(10));

    // Pavement
    for (u8 i = 0; i < 20; i++) {
        u8 tile = TILE_BKG(6 + (i % 4));
        set_bkg_tile_xy(PAVEMENT_COL + i, FLOOR_ROW, tile);
    }
}


void background_draw_grass(u8 col1, u8 row1, u8 col2, u8 row2)
{
    TILE_BKG_0 = TILE_BKG_0_floor;
    set_bkg_tile_xy(col1, row1, TILE_BKG(0));
    set_bkg_tile_xy(col2, row2, TILE_BKG(1));
}
