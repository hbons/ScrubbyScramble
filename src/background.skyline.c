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


#include "lib/extensions.h"
#include "lib/palettes.h"
#include "lib/tileset.h"

#include "background.skyline.h"


static u8 TILE_BKG_0;
u8 TILE_BKG_0_skyline;

const u8 moon_map[5][6] = {
    {  0,  2,  4,  6,  8,  0 },
    {  1,  3,  5,  7,  9, 11 },
    { 12, 14, 16, 18, 20, 22 },
    { 13, 15, 17, 19, 21, 23 },
    { 24, 26, 28, 30, 32, 34 }
};

const u8 city_map[][3] = {
    {  0, 17, true }, // row, col, big
    {  1, 17, false },
    {  9, 17, false },
    { 11, 17, true },
    { 12, 17, false },
    { 14, 17, true },
    { 15, 17, false },
    { 17, 17, false },
    { 24, 17, false },
    { 25, 17, true },
    { 27, 17, false },
    { 30, 17, false },
    { 31, 17, true },
    { 16, 18, false },
    { 18, 18, false },
    { 23, 18, false },
    { 26, 18, false },
    { 17, 19, false },
    { 19, 19, true },
    { 22, 19, true },
    { 24, 19, false },
};


#define MOON_COL 18
#define MOON_COL_MID (MOON_COL + 3)
#define MOON_ROW 13
#define STARS_ROW (MOON_ROW + 2)

u8 TILE_CITY_LEFT = 36;
u8 TILE_CITY_RIGHT = 37;
u8 TILE_CITY_LEFT_BIG = 39;
u8 TILE_CITY_RIGHT_BIG = 41;

void background_draw_skyline(void)
{
    TILE_BKG_0 = TILE_BKG_0_skyline;

    // City
    for (int i = 0; i != 21; i++) {
        u8 col = city_map[i][0];
        u8 row = city_map[i][1];
        u8 big = city_map[i][2];

        u8 tile = (col > MOON_COL_MID) ? TILE_CITY_RIGHT : TILE_CITY_LEFT;

        if (big) {
            tile = (col > MOON_COL_MID) ? TILE_CITY_RIGHT_BIG : TILE_CITY_LEFT_BIG;
            set_bkg_tile_xy(col, row - 1, TILE_BKG(tile - 1));
        }

        set_bkg_tile_xy(col, row, TILE_BKG(tile));
    }

    fill_attr_rect(0, 16, DEVICE_SCREEN_WIDTH, 9, S_PALETTE_3);


    // Stars left
    set_bkg_tile_xy(0, STARS_ROW, TILE_BKG(33));
    set_bkg_tile_xy(1, STARS_ROW, TILE_BKG(35));

    for (int i = 0; i != 3; i++)
        set_bkg_tile_xy(MOON_COL - 3 + i, STARS_ROW, TILE_BKG(25 + (2 * i)));


    // Moon
    for (u8 col = 0; col != 6; col++)
        for (u8 row = 0; row != 5; row++)
            set_bkg_tile_xy(MOON_COL + col, MOON_ROW + row, TILE_BKG(moon_map[row][col]));


    // Stars right
    for (int i = 0; i != 3; i++)
        set_bkg_tile_xy(MOON_COL + 6 + i, STARS_ROW, TILE_BKG(31 + (2 * i)));

    set_bkg_tile_xy(30, STARS_ROW, TILE_BKG(25));
    set_bkg_tile_xy(31, STARS_ROW, TILE_BKG(27));


    fill_attr_rect(0, 12, DEVICE_SCREEN_WIDTH, 4, S_PALETTE_2);
    fill_attr_rect(MOON_COL, MOON_ROW + 2, 6, 2, S_PALETTE_2);
}
