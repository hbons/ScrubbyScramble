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

#include "background.trees.h"


static u8 TILE_BKG_0;
u8 TILE_BKG_0_tree_solids;
u8 TILE_BKG_0_tree_left_1;
u8 TILE_BKG_0_tree_left_2;
u8 TILE_BKG_0_tree_left_3;
u8 TILE_BKG_0_tree_right_1;
u8 TILE_BKG_0_tree_right_2;
u8 TILE_BKG_0_tree_right_3;


void background_draw_trees(void)
{
    background_draw_solids();
    background_draw_trees_left();
    background_draw_trees_right();

    fill_attr_rect(0,  0, 10, 10, S_PALETTE_1);
    fill_attr_rect(22, 0, 10, 10, S_PALETTE_1);
}


void background_draw_solids(void)
{
    TILE_BKG_0 = TILE_BKG_0_tree_solids;

    u8 tile_solid_1 = TILE_BKG(0);
    u8 tile_solid_2 = TILE_BKG(1);
    u8 right = DEVICE_SCREEN_WIDTH - 1;

    // Left
    for (u8 x = 0; x != 5; x++)
        for (u8 y = 0; y != 5; y++)
            set_bkg_tile_xy(x, y, tile_solid_1);

    for (u8 i = 0; i != 3; i++) {
        set_bkg_tile_xy(7 + i, 0, tile_solid_2);
        set_bkg_tile_xy(0, 7 + i, tile_solid_2);
    }

    set_bkg_tile_xy(5, 0, tile_solid_1);
    set_bkg_tile_xy(0, 5, tile_solid_1);

    // Right
    for (u8 x = 0; x != 4; x++)
        for (u8 y = 0; y != 5; y++)
            set_bkg_tile_xy(right - x, y, tile_solid_2);

    for (u8 i = 0; i != 4; i++) {
        set_bkg_tile_xy(right - 9 + i, 0, tile_solid_1);
        set_bkg_tile_xy(right, 6 + i, tile_solid_1);
    }

    for (u8 i = 0; i != 3; i++)
        set_bkg_tile_xy(right - 4, i, tile_solid_2);
}


void background_draw_trees_left(void)
{
    // Tree left 1
    TILE_BKG_0 = TILE_BKG_0_tree_left_1;

    set_bkg_tile_xy(6,  0, TILE_BKG(0));
    set_bkg_tile_xy(10, 0, TILE_BKG(5));

    for (u8 i = 0; i != 4; i++)
        set_bkg_tile_xy(6 + i,  1, TILE_BKG(1 + i));


    // Tree left 2
    TILE_BKG_0 = TILE_BKG_0_tree_left_2;

    for (u8 i = 0; i != 3; i++)
        set_bkg_tile_xy(5, 1 + i, TILE_BKG(i));

    set_bkg_tile_xy(4, 3, TILE_BKG(3));
    set_bkg_tile_xy(4, 4, TILE_BKG(4));
    set_bkg_tile_xy(3, 5, TILE_BKG(5));
    set_bkg_tile_xy(2, 5, TILE_BKG(6));
    set_bkg_tile_xy(1, 5, TILE_BKG(7));
    set_bkg_tile_xy(1, 6, TILE_BKG(8));
    set_bkg_tile_xy(0, 6, TILE_BKG(9));


    // Tree left 3
    TILE_BKG_0 = TILE_BKG_0_tree_left_3;

    set_bkg_tile_xy(0,  10, TILE_BKG(3));

    for (u8 i = 0; i != 3; i++)
        set_bkg_tile_xy(1, 7 + i, TILE_BKG(i));
}


void background_draw_trees_right(void)
{
    // Tree right 1
    TILE_BKG_0 = TILE_BKG_0_tree_right_1;

    set_bkg_tile_xy(22,  0, TILE_BKG(0));

    for (u8 i = 0; i != 3; i++)
        set_bkg_tile_xy(23 + i,  1, TILE_BKG(1 + i));


    // Tree right 2
    TILE_BKG_0 = TILE_BKG_0_tree_right_2;

    for (u8 i = 0; i != 3; i++)
        set_bkg_tile_xy(26, i, TILE_BKG(i));

    set_bkg_tile_xy(27, 3, TILE_BKG(3));
    set_bkg_tile_xy(28, 4, TILE_BKG(4));
    set_bkg_tile_xy(29, 4, TILE_BKG(5));
    set_bkg_tile_xy(29, 5, TILE_BKG(6));
    set_bkg_tile_xy(30, 5, TILE_BKG(7));
    set_bkg_tile_xy(31, 5, TILE_BKG(8));


    // Tree right 3
    TILE_BKG_0 = TILE_BKG_0_tree_right_3;

    for (u8 i = 0; i != 4; i++)
        set_bkg_tile_xy(30, 6 + i, TILE_BKG(i));

    set_bkg_tile_xy(31, 10, TILE_BKG(4));
}
