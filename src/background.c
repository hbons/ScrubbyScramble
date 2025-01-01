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


#include "lib/tileset.h"

#include "background.h"
#include "background.floor.h"
#include "background.lamp.h"
#include "background.skyline.h"
#include "background.trees.h"


void background_init_tiles(void)
{
    TILE_BKG_0_tree_solids = tileset_init_bkg_tiles(tree_solids_TILE_COUNT, tree_solids_tiles);
    TILE_BKG_0_tree_left_1 = tileset_init_bkg_tiles(tree_left_1_TILE_COUNT, tree_left_1_tiles);
    TILE_BKG_0_tree_left_2 = tileset_init_bkg_tiles(tree_left_2_TILE_COUNT, tree_left_2_tiles);
    TILE_BKG_0_tree_left_3 = tileset_init_bkg_tiles(tree_left_3_TILE_COUNT, tree_left_3_tiles);
    TILE_BKG_0_tree_right_1 = tileset_init_bkg_tiles(tree_right_1_TILE_COUNT, tree_right_1_tiles);
    TILE_BKG_0_tree_right_2 = tileset_init_bkg_tiles(tree_right_2_TILE_COUNT, tree_right_2_tiles);
    TILE_BKG_0_tree_right_3 = tileset_init_bkg_tiles(tree_right_3_TILE_COUNT, tree_right_3_tiles);
    TILE_BKG_0_skyline = tileset_init_bkg_tiles(skyline_TILE_COUNT, skyline_tiles);
    TILE_BKG_0_floor = tileset_init_bkg_tiles(floor_TILE_COUNT, floor_tiles);
    TILE_BKG_0_lamp = tileset_init_bkg_tiles(lamp_TILE_COUNT, lamp_tiles);
}


void background_draw(void)
{
    background_draw_trees();
    background_draw_skyline();
    background_draw_lamp();
    background_draw_floor();
}
